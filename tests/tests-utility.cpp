/*
** Created by doom on 11/10/18.
*/

#include <ut_config.h>
#include <utility>
#include <type_traits>
#include <details/copy_constructible.hpp>

ut_test(move)
{
    int i = 1;

    static_assert(std::is_rvalue_reference_v<decltype(std::move(i))>);
}

static void dummy_function(const int &, int &&)
{
}

template <typename ...Args>
static void forwarding_function(Args &&...args)
{
    return dummy_function(std::forward<Args>(args)...);
}

ut_test(forward)
{
    int a = 1;
    int b = 2;

    forwarding_function(a, std::move(b));
}

ut_test(integer_sequence)
{
    using size_t_seq_5 = std::make_index_sequence<5>;
    using int_seq_10 = std::make_integer_sequence<int, 10>;

    static_assert(std::is_same_v<size_t_seq_5, std::index_sequence<0, 1, 2, 3, 4>>);
    static_assert(std::is_same_v<int_seq_10, std::integer_sequence<int, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9>>);
}

namespace
{
    struct default_constructible
    {
        default_constructible() = default;
    };

    struct explicitly_default_constructible
    {
        explicit explicitly_default_constructible() = default;
    };
}

ut_test(details)
{
    static_assert(std::more::is_implicitly_default_constructible_v<int>);
    static_assert(std::more::is_implicitly_default_constructible_v<default_constructible>);
    static_assert(!std::more::is_implicitly_default_constructible_v<explicitly_default_constructible>);
    static_assert(!std::more::is_implicitly_default_constructible_v<std::reference_wrapper<int>>);
}

using int_and_float = std::pair<int, float>;
using int_and_float_taker = void (*)(const int_and_float &);
using float_and_float_taker = void (*)(const std::pair<float, float> &);

using int_and_edc = std::pair<int, explicitly_default_constructible>;
using int_and_edc_taker = void (*)(int_and_edc);

using int_and_ncc = std::pair<int, std::details::not_copy_constructible>;

#define GENERATE_CAN_TAKE_CHECKER(name, ...)                                                                \
template <typename FuncT, typename T = void>                                                                \
struct name : std::false_type                                                                               \
{                                                                                                           \
};                                                                                                          \
                                                                                                            \
template <typename FuncT>                                                                                   \
struct name <FuncT, decltype(std::declval<FuncT>()(__VA_ARGS__))> : std::true_type                          \
{                                                                                                           \
};

namespace
{
    GENERATE_CAN_TAKE_CHECKER(can_take_implicit_int_and_float, { 1, 2.3 });
    GENERATE_CAN_TAKE_CHECKER(can_take_implicit_int_and_edc, {});
    GENERATE_CAN_TAKE_CHECKER(can_take_int_and_float, int_and_float{1, 2.3});
    GENERATE_CAN_TAKE_CHECKER(can_take_int_and_edc, int_and_edc{});

    GENERATE_CAN_TAKE_CHECKER(can_convert_implicitly_from_int_and_float, int_and_float{1, 2.3});
}

template <template <typename...> typename T, typename F>
inline constexpr const bool verify = T<F>::value;

ut_test(pair)
{
    static_assert(std::more::is_implicitly_default_constructible_v<int_and_float>);
    static_assert(!std::more::is_implicitly_default_constructible_v<int_and_edc>);

    static_assert(std::is_copy_constructible_v<int_and_float>);
    static_assert(std::is_copy_constructible_v<int_and_edc>);
    static_assert(!std::is_copy_constructible_v<int_and_ncc>);

    static_assert(verify<can_take_implicit_int_and_float, int_and_float_taker>);
    static_assert(!verify<can_take_implicit_int_and_edc, int_and_edc_taker>);
    static_assert(verify<can_take_int_and_float, int_and_float_taker>);
    static_assert(verify<can_take_int_and_edc, int_and_edc_taker>);

    static_assert(verify<can_convert_implicitly_from_int_and_float, float_and_float_taker>);
    static_assert(!verify<can_convert_implicitly_from_int_and_float, int_and_edc_taker>);

    std::pair<int, int> p(1, 2);

    int_and_float p1(2, 2.3);
    p1 = p;
    ut_assert_eq(p1.first, 1);
    ut_assert_eq(p1.second, 2);

    int_and_float p2(2, 2.3);
    p2 = std::move(p);
    ut_assert_eq(p2.first, 1);
    ut_assert_eq(p2.second, 2);
}

ut_group(utility,
         ut_get_test(move),
         ut_get_test(forward),
         ut_get_test(integer_sequence),
         ut_get_test(details),
         ut_get_test(pair)
);

void run_utility_tests()
{
    ut_run_group(ut_get_group(utility));
}

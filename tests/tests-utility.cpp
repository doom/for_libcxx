/*
** Created by doom on 11/10/18.
*/

#include <ut_config.h>
#include <utility>
#include <type_traits>

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

ut_group(utility,
         ut_get_test(move),
         ut_get_test(forward),
         ut_get_test(integer_sequence)
);

void run_utility_tests()
{
    ut_run_group(ut_get_group(utility));
}

/*
** Created by doom on 09/10/18.
*/

#include <ut_config.h>
#include <type_traits>

ut_test(integral_constant)
{
    using type1 = std::integral_constant<int, 3>;

    static_assert(type1::value == 3);
    static_assert(type1{}() == 3);
    static_assert((int)type1{} == 3);
}

ut_test(bool_constant)
{
    using false_t = std::bool_constant<false>;
    static_assert(false_t::value == false);

    using true_t = std::bool_constant<true>;
    static_assert(true_t::value == true);
}

ut_test(true_type)
{
    static_assert(std::true_type::value == true);
}

ut_test(false_type)
{
    static_assert(std::false_type::value == false);
}

ut_test(is_same)
{
    using type1 = int;
    using type2 = const int;
    using type3 = float;

    static_assert(std::is_same_v<type1, type1>);
    static_assert(!std::is_same_v<type1, type2>);
    static_assert(!std::is_same_v<type1, type3>);
    static_assert(!std::is_same_v<type2, type3>);
}

ut_test(is_const)
{
    static_assert(std::is_const_v<const int>);
    static_assert(!std::is_const_v<int>);
    static_assert(std::is_const_v<int *const>);
    static_assert(!std::is_const_v<const int *>);
}

ut_test(is_lvalue_reference)
{
    static_assert(std::is_lvalue_reference_v<const int &>);
    static_assert(!std::is_lvalue_reference_v<int>);
    static_assert(std::is_lvalue_reference_v<int &>);
    static_assert(!std::is_lvalue_reference_v<const int *>);
}

ut_test(is_rvalue_reference)
{
    static_assert(std::is_rvalue_reference_v<const int &&>);
    static_assert(!std::is_rvalue_reference_v<int>);
    static_assert(std::is_rvalue_reference_v<int &&>);
    static_assert(!std::is_rvalue_reference_v<const int *>);
}

ut_test(remove_const)
{
    static_assert(std::is_same_v<std::remove_const_t<const int>, int>);
    static_assert(std::is_same_v<std::remove_const_t<int>, int>);
    static_assert(std::is_same_v<std::remove_const_t<const int *>, const int *>);
    static_assert(std::is_same_v<std::remove_const_t<int *const>, int *>);
}

ut_test(remove_volatile)
{
    static_assert(std::is_same_v<std::remove_volatile_t<volatile int>, int>);
    static_assert(std::is_same_v<std::remove_volatile_t<int>, int>);
    static_assert(std::is_same_v<std::remove_volatile_t<int *volatile>, int *>);
}

ut_test(add_const)
{
    static_assert(std::is_same_v<std::add_const_t<int>, const int>);
    static_assert(std::is_same_v<std::add_const_t<const int>, const int>);
    static_assert(std::is_same_v<std::add_const_t<int *>, int *const>);
}

ut_test(add_volatile)
{
    static_assert(std::is_same_v<std::add_volatile_t<int>, volatile int>);
    static_assert(std::is_same_v<std::add_volatile_t<volatile int>, volatile int>);
    static_assert(std::is_same_v<std::add_volatile_t<int *>, int *volatile>);
}

ut_test(is_void)
{
    static_assert(std::is_void_v<void>);
    static_assert(!std::is_void_v<int>);
}

ut_test(is_constructible)
{
    static_assert(std::is_constructible_v<int, int>);
    static_assert(!std::is_constructible_v<int, const char *>);
}

namespace
{
    class not_move_constructible
    {
    public:
        not_move_constructible(not_move_constructible &&) = delete;
    };

    class throw_move_constructible
    {
    public:
        throw_move_constructible(throw_move_constructible &&)
        {
            throw 1;
        }
    };

    class nothrow_move_constructible
    {
    public:
        nothrow_move_constructible(nothrow_move_constructible &&) noexcept = default;
    };
}

ut_test(is_move_constructible)
{
    static_assert(std::is_move_constructible_v<nothrow_move_constructible>);
    static_assert(std::is_move_constructible_v<throw_move_constructible>);
    static_assert(!std::is_move_constructible_v<not_move_constructible>);

    static_assert(std::is_nothrow_move_constructible_v<nothrow_move_constructible>);
    static_assert(!std::is_nothrow_move_constructible_v<throw_move_constructible>);
    static_assert(!std::is_nothrow_move_constructible_v<not_move_constructible>);
}

ut_group(type_traits,
         ut_get_test(integral_constant),
         ut_get_test(bool_constant),
         ut_get_test(true_type),
         ut_get_test(false_type),
         ut_get_test(is_same),
         ut_get_test(is_const),
         ut_get_test(is_lvalue_reference),
         ut_get_test(is_rvalue_reference),
         ut_get_test(remove_const),
         ut_get_test(remove_volatile),
         ut_get_test(add_const),
         ut_get_test(add_volatile),
         ut_get_test(is_void),
         ut_get_test(is_constructible),
         ut_get_test(is_move_constructible)
);

void run_type_traits_tests()
{
    ut_run_group(ut_get_group(type_traits));
}

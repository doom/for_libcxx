/*
** Created by doom on 09/10/18.
*/

#include <ut_config.h>
#include <type_traits>
#include <utility>

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

ut_test(is_volatile)
{
    static_assert(std::is_volatile_v<volatile int>);
    static_assert(!std::is_volatile_v<int>);
    static_assert(std::is_volatile_v<int *volatile>);
    static_assert(!std::is_volatile_v<volatile int *>);
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

ut_test(add_pointer)
{
    static_assert(std::is_same_v<std::add_pointer_t<int>, int *>);
    static_assert(std::is_same_v<std::add_pointer_t<void(int, int)>, void (*)(int, int)>);
    static_assert(std::is_same_v<std::add_pointer_t<void (&)(int, int)>, void (&)(int, int)>);
}

ut_test(is_void)
{
    static_assert(std::is_void_v<void>);
    static_assert(!std::is_void_v<int>);
}

ut_test(is_pointer)
{
    static_assert(std::is_pointer_v<int *>);
    static_assert(!std::is_pointer_v<int>);
    static_assert(std::is_pointer_v<int **>);
    static_assert(!std::is_pointer_v<int &>);
    static_assert(!std::is_pointer_v<int[]>);
}

ut_test(is_array)
{
    static_assert(std::is_array_v<int[]>);
    static_assert(std::is_array_v<int[42]>);
    static_assert(!std::is_array_v<int *>);
    static_assert(!std::is_array_v<void (*)(int)>);
    static_assert(!std::is_array_v<int &>);
    static_assert(!std::is_array_v<int>);
}

namespace
{
    struct x
    {
    };
}

ut_test(is_integral)
{
    static_assert(std::is_integral_v<int>);
    static_assert(std::is_integral_v<unsigned int>);
    static_assert(!std::is_unsigned_v<float>);
    static_assert(!std::is_unsigned_v<x>);
    static_assert(std::is_integral_v<const volatile int>);
    static_assert(std::is_integral_v<const volatile unsigned int>);
    static_assert(!std::is_unsigned_v<const volatile float>);
    static_assert(!std::is_unsigned_v<const volatile x>);
    static_assert(!std::is_unsigned_v<int *>);
}

ut_test(is_floating_point)
{
    static_assert(std::is_floating_point_v<float>);
    static_assert(std::is_floating_point_v<double>);
    static_assert(std::is_floating_point_v<long double>);
    static_assert(!std::is_floating_point_v<int>);
    static_assert(!std::is_unsigned_v<x>);
    static_assert(std::is_floating_point_v<const volatile float>);
    static_assert(std::is_floating_point_v<const volatile double>);
    static_assert(std::is_floating_point_v<const volatile long double>);
    static_assert(!std::is_floating_point_v<const volatile int>);
    static_assert(!std::is_unsigned_v<const volatile x>);
    static_assert(!std::is_unsigned_v<int *>);
}

ut_test(is_unsigned)
{
    static_assert(!std::is_unsigned_v<int>);
    static_assert(std::is_unsigned_v<unsigned int>);
    static_assert(!std::is_unsigned_v<signed char>);
    static_assert(!std::is_unsigned_v<x>);

    static_assert(!std::is_unsigned_v<const volatile int>);
    static_assert(std::is_unsigned_v<const volatile unsigned int>);
    static_assert(!std::is_unsigned_v<const volatile signed char>);
    static_assert(!std::is_unsigned_v<const volatile x>);
    static_assert(!std::is_unsigned_v<int *>);
}

namespace
{
    struct is_function_test
    {
        void member_func()
        {

        }
    };

    void is_function_test_f1(int, int)
    {

    }

    int is_function_test_f2(int, float, ...)
    {
        return 0;
    }
}

ut_test(is_function)
{
    static_assert(!std::is_function_v<int>);
    static_assert(!std::is_function_v<decltype(&is_function_test::member_func)>);
    static_assert(std::is_function_v<decltype(is_function_test_f1)>);
    static_assert(std::is_function_v<decltype(is_function_test_f2)>);
}

namespace
{
    class not_trivially_constructible
    {
    public:
        not_trivially_constructible(int v) noexcept : _value(v + 2)
        {
        }

    private:
        int _value;
    };

    class throw_constructible
    {
    public:
        throw_constructible()
        {
            throw 1;
        }
    };
}

ut_test(is_constructible)
{
    static_assert(std::is_constructible_v<int, int>);
    static_assert(!std::is_constructible_v<int, const char *>);

    static_assert(std::is_trivially_constructible_v<int, int>);
    static_assert(!std::is_trivially_constructible_v<int, const char *>);
    static_assert(!std::is_trivially_constructible_v<not_trivially_constructible>);
    static_assert(!std::is_trivially_constructible_v<not_trivially_constructible, int>);

    static_assert(std::is_nothrow_constructible_v<not_trivially_constructible, int>);
    static_assert(!std::is_nothrow_constructible_v<throw_constructible>);
}

namespace
{
    struct not_trivially_move_constructible
    {
        not_trivially_move_constructible(not_trivially_move_constructible &&other) : _value(other._value + 2)
        {
        }

        int _value{0};
    };

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

    static_assert(std::is_trivially_move_constructible_v<int>);
    static_assert(!std::is_trivially_move_constructible_v<not_trivially_move_constructible>);

    static_assert(std::is_nothrow_move_constructible_v<nothrow_move_constructible>);
    static_assert(!std::is_nothrow_move_constructible_v<throw_move_constructible>);
    static_assert(!std::is_nothrow_move_constructible_v<not_move_constructible>);
}

namespace
{
    class not_trivially_assignable
    {
    public:
        not_trivially_assignable &operator=(int v) noexcept
        {
            _value = v + 2;
            return *this;
        }

    private:
        int _value;
    };

    class throw_assignable
    {
    public:
        throw_assignable &operator=(int)
        {
            throw 1;
        }
    };
}

ut_test(is_assignable)
{
    static_assert(!std::is_assignable_v<int, int>);
    static_assert(std::is_assignable_v<int &, int>);
    static_assert(!std::is_assignable_v<int, const char *>);
    static_assert(!std::is_assignable_v<int &, const char *>);

    static_assert(std::is_trivially_assignable_v<int &, int>);
    static_assert(!std::is_trivially_assignable_v<int &, const char *>);
    static_assert(!std::is_trivially_assignable_v<not_trivially_assignable &, int>);

    static_assert(std::is_nothrow_assignable_v<not_trivially_assignable &, int>);
    static_assert(!std::is_nothrow_assignable_v<throw_assignable &, int>);
}

namespace
{
    struct not_trivially_move_assignable
    {
        not_trivially_move_assignable &operator=(not_trivially_move_assignable &&other) noexcept
        {
            _value = other._value + 2;
            return *this;
        }

        int _value{0};
    };

    class not_move_assignable
    {
    public:
        not_move_assignable &operator=(not_move_assignable &&) = delete;
    };

    class throw_move_assignable
    {
    public:
        throw_move_assignable &operator=(throw_move_assignable &&)
        {
            throw 1;
            return *this;
        }
    };

    class nothrow_move_assignable
    {
    public:
        nothrow_move_assignable &operator=(nothrow_move_assignable &&) noexcept = default;
    };
}

ut_test(is_move_assignable)
{
    static_assert(std::is_move_assignable_v<nothrow_move_assignable>);
    static_assert(std::is_move_assignable_v<throw_move_assignable>);
    static_assert(!std::is_move_assignable_v<not_move_assignable>);

    static_assert(std::is_trivially_move_assignable_v<int>);
    static_assert(!std::is_trivially_move_assignable_v<not_trivially_move_assignable>);

    static_assert(std::is_nothrow_move_assignable_v<nothrow_move_assignable>);
    static_assert(!std::is_nothrow_move_assignable_v<throw_move_assignable>);
    static_assert(!std::is_nothrow_move_assignable_v<not_move_assignable>);
}

namespace
{
    struct destructible
    {
    };

    class not_destructible
    {
    public:
        ~not_destructible() = delete;
    };

    class throw_destructible
    {
    public:
        ~throw_destructible() noexcept(false)
        {
            throw 1;
        }
    };
}

ut_test(is_destructible)
{
    static_assert(std::is_destructible_v<int>);
    static_assert(std::is_destructible_v<destructible>);
    static_assert(!std::is_destructible_v<not_destructible>);

    static_assert(std::is_trivially_destructible_v<int>);
    static_assert(std::is_trivially_destructible_v<destructible>);
    static_assert(!std::is_trivially_destructible_v<not_destructible>);

    static_assert(std::is_nothrow_destructible_v<int>);
    static_assert(std::is_nothrow_destructible_v<destructible>);
    static_assert(!std::is_nothrow_destructible_v<throw_destructible>);
    static_assert(!std::is_nothrow_destructible_v<not_destructible>);
}

namespace
{
    struct dummy_struct
    {
        double d;
        int i;
    };
}

ut_test(conditional)
{
    using T1 = std::conditional_t<true, int, float>;
    static_assert(std::is_same_v<T1, int>);

    using T2 = std::conditional_t<false, int, float>;
    static_assert(std::is_same_v<T2, float>);
}

ut_test(decay)
{
    using T1 = std::decay_t<int>;
    static_assert(std::is_same_v<int, T1>);

    using T2 = std::decay_t<int &>;
    static_assert(std::is_same_v<int, T2>);

    using T3 = std::decay_t<const int &>;
    static_assert(std::is_same_v<int, T3>);

    using T4 = std::decay_t<const int[200]>;
    static_assert(std::is_same_v<const int *, T4>);

    using T5 = std::decay_t<int(float, int)>;
    static_assert(std::is_same_v<int (*)(float, int), T5>);
}

ut_test(aligned_storage)
{
    using int_storage = std::aligned_storage_t<sizeof(int), alignof(int)>;
    static_assert(sizeof(int_storage) >= sizeof(int));
    static_assert(alignof(int_storage) >= alignof(int));

    using char_storage = std::aligned_storage_t<sizeof(char), alignof(char)>;
    static_assert(sizeof(char_storage) >= sizeof(char));
    static_assert(alignof(char_storage) >= alignof(char));

    using dummy_struct_storage = std::aligned_storage_t<sizeof(dummy_struct), alignof(dummy_struct)>;
    static_assert(sizeof(dummy_struct_storage) >= sizeof(dummy_struct));
    static_assert(alignof(dummy_struct_storage) >= alignof(dummy_struct));
}

ut_test(make_unsigned)
{
    static_assert(std::is_same_v<std::make_unsigned_t<int>, unsigned int>);
    static_assert(std::is_same_v<std::make_unsigned_t<const int>, const unsigned int>);
    static_assert(std::is_same_v<std::make_unsigned_t<volatile int>, volatile unsigned int>);
    static_assert(std::is_same_v<std::make_unsigned_t<const volatile int>, const volatile unsigned int>);
    static_assert(std::is_same_v<std::make_unsigned_t<float>, float>);
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
         ut_get_test(add_pointer),
         ut_get_test(is_void),
         ut_get_test(is_pointer),
         ut_get_test(is_array),
         ut_get_test(is_integral),
         ut_get_test(is_floating_point),
         ut_get_test(is_unsigned),
         ut_get_test(is_function),
         ut_get_test(is_constructible),
         ut_get_test(is_move_constructible),
         ut_get_test(is_assignable),
         ut_get_test(is_move_assignable),
         ut_get_test(is_destructible),
         ut_get_test(conditional),
         ut_get_test(decay),
         ut_get_test(aligned_storage),
         ut_get_test(make_unsigned),
);

void run_type_traits_tests()
{
    ut_run_group(ut_get_group(type_traits));
}

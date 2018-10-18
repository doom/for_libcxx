/*
** Created by doom on 13/10/18.
*/

#include <ut_config.h>

#include <optional>

ut_test(nullopt)
{
    static_assert(std::is_same_v<std::remove_cv_t<decltype(std::nullopt)>, std::nullopt_t>);
}

namespace
{
    class not_trivially_destructible
    {
    public:
        ~not_trivially_destructible()
        {
        }
    };

    class throw_move_constructible
    {
        throw_move_constructible(throw_move_constructible &&) noexcept(false)
        {
        }
    };

    class throw_destructible
    {
        ~throw_destructible() noexcept(false)
        {
        }
    };

    class non_copyable
    {
    public:
        non_copyable() = default;

        non_copyable(const non_copyable &) = delete;

        non_copyable(non_copyable &&) = default;
    };

    class non_movable
    {
    public:
        non_movable() = default;

        non_movable(const non_movable &) = default;

        non_movable(non_movable &&) = delete;
    };
}

template <typename T>
constexpr const bool check_same_noexceptness =
    std::is_nothrow_destructible_v<T> == std::is_nothrow_destructible_v<std::optional<T>>
    && std::is_nothrow_move_constructible_v<T> == std::is_nothrow_move_constructible_v<std::optional<T>>
    && std::is_nothrow_copy_constructible_v<T> == std::is_nothrow_copy_constructible_v<std::optional<T>>
    && (std::is_nothrow_destructible_v<T>
        && std::is_nothrow_move_constructible_v<T>
        && std::is_nothrow_move_assignable_v<T>) == std::is_nothrow_move_assignable_v<std::optional<T>>
    && (std::is_nothrow_copy_assignable_v<T>
        && std::is_nothrow_copy_constructible_v<T>
        && std::is_nothrow_copy_assignable_v<T>) == std::is_nothrow_copy_assignable_v<std::optional<T>>;

template <typename T>
constexpr const bool check_same_triviality =
    std::is_trivially_destructible_v<T> == std::is_trivially_destructible_v<std::optional<T>>
    && std::is_trivially_move_constructible_v<T> == std::is_trivially_move_constructible_v<std::optional<T>>
    && std::is_trivially_copy_constructible_v<T> == std::is_trivially_copy_constructible_v<std::optional<T>>
    && (std::is_trivially_destructible_v<T>
        && std::is_trivially_move_constructible_v<T>
        && std::is_trivially_move_assignable_v<T>) == std::is_trivially_move_assignable_v<std::optional<T>>
    && (std::is_trivially_copy_assignable_v<T>
        && std::is_trivially_copy_constructible_v<T>
        && std::is_trivially_copy_assignable_v<T>) == std::is_trivially_copy_assignable_v<std::optional<T>>;

ut_test(traits)
{
    using opt_int = std::optional<int>;
    static_assert(std::is_copy_constructible_v<opt_int>);
    static_assert(std::is_move_constructible_v<opt_int>);
    static_assert(std::is_trivially_destructible_v<opt_int>);
    static_assert(std::is_trivially_move_constructible_v<opt_int>);
    static_assert(std::is_trivially_copy_constructible_v<opt_int>);

    static_assert(std::is_nothrow_move_constructible_v<opt_int>);
    static_assert(std::is_nothrow_copy_constructible_v<opt_int>);
    static_assert(std::is_nothrow_move_assignable_v<opt_int>);
    static_assert(std::is_nothrow_copy_assignable_v<opt_int>);

    static_assert(!std::is_trivially_destructible_v<not_trivially_destructible>);

    static_assert(not std::is_copy_constructible_v<std::optional<non_copyable>>);
    static_assert(std::is_move_constructible_v<std::optional<non_copyable>>);

    static_assert(check_same_noexceptness<int>);
    static_assert(check_same_noexceptness<throw_move_constructible>);
    static_assert(check_same_noexceptness<not_trivially_destructible>);
    static_assert(check_same_noexceptness<throw_destructible>);

    static_assert(check_same_triviality<int>);
    static_assert(check_same_triviality<throw_move_constructible>);
    static_assert(check_same_triviality<not_trivially_destructible>);
}

ut_test(non_movable_to_copy)
{
    std::optional<non_movable> nmv1;
    nmv1.emplace();
    ut_assert(nmv1.has_value());
    std::optional<non_movable> nmv2(std::move(nmv1));
    ut_assert(nmv2.has_value());
    ut_assert(nmv1.has_value());
}

ut_test(basic_usage)
{
    constexpr std::optional<int> o1;
    static_assert(not o1.has_value());

    constexpr std::optional<int> o2(std::nullopt);
    static_assert(not o2.has_value());

    std::optional<int> o3;
    o3.emplace(1234);
    ut_assert(o3.has_value());
    ut_assert_eq(*o3, 1234);

    o3.reset();
    ut_assert(not o3.has_value());

    std::optional<int> o4(5678);
    ut_assert(o4.has_value());
    ut_assert_eq(*o4, 5678);
}

namespace
{
    class move_test
    {
    public:
        enum flag
        {
            ValueB,
            MovedFrom,
        };

        move_test(flag f) noexcept : status{f}
        {
        }

        move_test(move_test &&other) noexcept : status(other.status)
        {
            other.status = MovedFrom;
        }

        move_test(const move_test &) = default;

        move_test &operator=(move_test &&) noexcept = default;

        move_test &operator=(const move_test &) = default;

        flag status;
    };
}

ut_test(copy_move)
{
    std::optional<move_test> mv1(move_test::ValueB);
    ut_assert(mv1.has_value());
    ut_assert_eq(mv1->status, move_test::ValueB);

    std::optional<move_test> mv2(mv1);
    ut_assert(mv2.has_value());
    ut_assert_eq(mv2->status, move_test::ValueB);

    std::optional<move_test> mv3(std::move(mv1));
    ut_assert(mv3.has_value());
    ut_assert_eq(mv3->status, move_test::ValueB);
    ut_assert(mv1.has_value());
    ut_assert_eq(mv1->status, move_test::MovedFrom);
}

namespace
{
    class move_fallback_test
    {
    public:
        enum flag
        {
            ValueB,
            CopiedTo,
        };

        move_fallback_test(flag f) noexcept : status{f}
        {
        }

        move_fallback_test(const move_fallback_test &) : status(CopiedTo)
        {
        }

        move_fallback_test(move_test &&) noexcept = delete;

        move_fallback_test &operator=(move_fallback_test &&) noexcept = default;

        move_fallback_test &operator=(const move_fallback_test &) = default;

        flag status;
    };
}

ut_test(move_fallback_to_copy)
{
    std::optional<move_fallback_test> mv1(move_fallback_test::ValueB);
    std::optional<move_fallback_test> mv2(std::move(mv1));
    ut_assert_eq(mv2->status, move_fallback_test::CopiedTo);
}

ut_test(value_or)
{
    constexpr std::optional<int> empty;
    ut_assert_eq(empty.value_or(4321), 4321);

    constexpr std::optional<int> o1(8765);
    ut_assert_eq(o1.value_or(4321), 8765);
}

/** Enable this code if exception support is activated */
#if 0
ut_test(exceptions)
{
    std::optional<int> empty;

    ut_assert_throw(empty.value(), std::bad_optional_access);
}
#endif

ut_group(optional,
         ut_get_test(nullopt),
         ut_get_test(non_movable_to_copy),
         ut_get_test(basic_usage),
         ut_get_test(copy_move),
         ut_get_test(move_fallback_to_copy),
         ut_get_test(value_or),
);

void run_optional_tests()
{
    ut_run_group(ut_get_group(optional));
}

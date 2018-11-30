/*
** Created by doom on 28/11/18.
*/

#include <ut_config.h>
#include <tuple>
#include <type_traits>

ut_test(tuple_element)
{
    using int_float_double = std::tuple<int, float, double>;

    static_assert(std::is_same_v<std::tuple_element_t<0, int_float_double>, int>);
    static_assert(std::is_same_v<std::tuple_element_t<1, int_float_double>, float>);
    static_assert(std::is_same_v<std::tuple_element_t<2, int_float_double>, double>);
}

namespace
{
    struct default_constructible
    {
    };
}

ut_test(get)
{
    constexpr std::tuple<default_constructible, default_constructible, default_constructible> t;
    constexpr std::tuple<int, float, double> t2(1, 1.0, 4.5);

    static_assert(std::get<0>(t2) == 1);
    static_assert(std::get<1>(t2) == 1.0);
    static_assert(std::get<2>(t2) == 4.5);
}

ut_test(copy_construction)
{
    constexpr std::tuple<int, float, double> t1(1, 1.0, 4.5);

    static_assert(std::get<0>(t1) == 1);
    static_assert(std::get<1>(t1) == 1.0);
    static_assert(std::get<2>(t1) == 4.5);

    constexpr auto t2(t1);
    static_assert(std::get<0>(t2) == 1);
    static_assert(std::get<1>(t2) == 1.0);
    static_assert(std::get<2>(t2) == 4.5);
}

ut_test(move_construction)
{
    constexpr std::tuple<int, float, double> t1(1, 1.0, 4.5);

    static_assert(std::get<0>(t1) == 1);
    static_assert(std::get<1>(t1) == 1.0);
    static_assert(std::get<2>(t1) == 4.5);

    constexpr auto t2(std::move(t1));
    static_assert(std::get<0>(t2) == 1);
    static_assert(std::get<1>(t2) == 1.0);
    static_assert(std::get<2>(t2) == 4.5);
}

ut_test(comparisons)
{
    constexpr std::tuple<int, float, double> t2(1, 1.0, 4.5);
    constexpr std::tuple<int, float, double> t3(1, 1.0, 3.2);
    constexpr std::tuple<int, float, double> t4(2, 2.0, 5.2);

    static_assert(t2 == t2);
    static_assert(t2 <= t2);
    static_assert(t2 >= t2);
    static_assert(t2 <= t3);
    static_assert(t3 >= t2);
    static_assert(t4 > t2);
    static_assert(t2 < t4);
}

ut_group(tuple,
         ut_get_test(tuple_element),
         ut_get_test(get),
         ut_get_test(copy_construction),
         ut_get_test(move_construction),
         ut_get_test(comparisons)
);

void run_tuple_tests()
{
    ut_run_group(ut_get_group(tuple));
}

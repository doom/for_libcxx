/*
** Created by doom on 09/01/19.
*/

#include <ut_config.h>
#include <numeric>
#include <iterator>

ut_test(accumulate)
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    auto v1 = std::accumulate(std::begin(arr), std::end(arr), 0);
    ut_assert_eq(v1, 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10);

    auto v2 = std::accumulate(std::begin(arr), std::end(arr), 1, [](auto &&a, auto &&b) {
        return a * b;
    });
    ut_assert_eq(v2, 1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
}

ut_group(numeric,
         ut_get_test(accumulate)
);

void run_numeric_tests()
{
    ut_run_group(ut_get_group(numeric));
}

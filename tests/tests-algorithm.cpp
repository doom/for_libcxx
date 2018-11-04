/*
** Created by doom on 03/11/18.
*/

#include <ut_config.h>
#include <algorithm>

ut_test(min_element)
{
    int arr1[] = {1, 2, 1, 4, 5};

    auto it1 = std::min_element(std::begin(arr1), std::end(arr1));
    ut_assert_eq(it1, std::begin(arr1));

    auto it2 = std::min_element(std::begin(arr1) + 1, std::begin(arr1) + 1);
    ut_assert_eq(it2, std::begin(arr1) + 1);

    auto it3 = std::min_element(std::end(arr1), std::end(arr1));
    ut_assert_eq(it3, std::end(arr1));

    auto it4 = std::min_element(std::begin(arr1), std::end(arr1), [](const auto &a, const auto &b) {
        return -a < -b;
    });
    ut_assert_eq(it4, std::begin(arr1) + 4);
}

ut_test(max_element)
{
    int arr1[] = {1, 2, 1, 4, 5};

    auto it1 = std::max_element(std::begin(arr1), std::end(arr1));
    ut_assert_eq(it1, std::begin(arr1) + 4);

    auto it2 = std::max_element(std::begin(arr1) + 1, std::begin(arr1) + 1);
    ut_assert_eq(it2, std::begin(arr1) + 1);

    auto it3 = std::max_element(std::end(arr1), std::end(arr1));
    ut_assert_eq(it3, std::end(arr1));

    auto it4 = std::max_element(std::begin(arr1), std::end(arr1), [](const auto &a, const auto &b) {
        return -a < -b;
    });
    ut_assert_eq(it4, std::begin(arr1));
}

ut_group(algorithm,
         ut_get_test(min_element),
         ut_get_test(max_element)
);

void run_algorithm_tests()
{
    ut_run_group(ut_get_group(algorithm));
}

/*
** Created by doom on 03/11/18.
*/

#include <ut_config.h>
#include <algorithm>
#include <string_view>

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

ut_test(for_each)
{
    int arr1[] = {2, 3, 4, 2, 1, 9};

    size_t n = 0;
    std::for_each(std::begin(arr1), std::end(arr1), [&](const auto &a) {
        ut_assert_eq(&arr1[n], &a);
        ++n;
    });
}

ut_test(find_if)
{
    int arr1[] = {0, 2, 2, 1, 4, 1};

    auto it = std::find_if(std::begin(arr1), std::end(arr1), [](const auto &a) {
        return a == 1;
    });
    ut_assert_eq(it, std::begin(arr1) + 3);

    auto it2 = std::find_if(std::begin(arr1), std::end(arr1), [](const auto &a) {
        return a == 0;
    });
    ut_assert_eq(it2, std::begin(arr1));

    auto it3 = std::find_if(std::begin(arr1), std::end(arr1), [](const auto &a) {
        return a == 32;
    });
    ut_assert_eq(it3, std::end(arr1));
}

ut_test(all_of)
{
    int evens[] = {2, 4, 6, 8, 10};

    bool r1 = std::all_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 == 0;
    });
    ut_assert(r1);

    bool r2 = std::all_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n == 2;
    });
    ut_assert_false(r2);

    bool r3 = std::all_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 != 0;
    });
    ut_assert_false(r3);
}

ut_test(any_of)
{
    int evens[] = {2, 4, 6, 8, 10};

    bool r1 = std::any_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 == 0;
    });
    ut_assert(r1);

    bool r2 = std::any_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n == 4;
    });
    ut_assert(r2);

    bool r3 = std::any_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 != 0;
    });
    ut_assert_false(r3);
}

ut_test(none_of)
{
    int evens[] = {2, 4, 6, 8, 10};

    bool r1 = std::none_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 == 0;
    });
    ut_assert_false(r1);

    bool r2 = std::none_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n == 4;
    });
    ut_assert_false(r2);

    bool r3 = std::none_of(std::begin(evens), std::end(evens), [](const auto &n) {
        return n % 2 != 0;
    });
    ut_assert(r3);
}

ut_test(transform)
{
    constexpr std::string_view s{"salut"};
    int distances_to_a[5] = {0};

    auto it = std::transform(s.begin(), s.end(), std::begin(distances_to_a), [](const auto c) {
        return c - 'a';
    });
    ut_assert_eq(it, std::end(distances_to_a));
    size_t i = 0;
    for (const auto c : s) {
        ut_assert_eq(c - 'a', distances_to_a[i++]);
    }

    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};
    int result[5] = {0};

    auto it2 = std::transform(std::begin(arr1), std::end(arr1), std::begin(arr2), std::begin(result),
                              [](auto a, auto b) {
                                  return a + b;
                              });
    ut_assert_eq(it2, std::end(result));
    ut_assert(std::all_of(std::begin(result), std::end(result), [](auto i) {
        return i == 6;
    }));
}

ut_group(algorithm,
         ut_get_test(min_element),
         ut_get_test(max_element),
         ut_get_test(for_each),
         ut_get_test(find_if),
         ut_get_test(all_of),
         ut_get_test(any_of),
         ut_get_test(none_of),
         ut_get_test(transform)
);

void run_algorithm_tests()
{
    ut_run_group(ut_get_group(algorithm));
}

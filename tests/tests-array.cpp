/*
** Created by doom on 22/02/19.
*/

#include <ut_config.h>
#include <array>

ut_test(size)
{
    constexpr std::array<int, 3> arr1{};
    constexpr std::array<int, 0> arr2{};

    static_assert(arr1.size() == 3);
    static_assert(arr1.max_size() == 3);
    static_assert(not arr1.empty());
    static_assert(arr2.empty());
}

ut_test(access)
{
    std::array<int, 3> arr1{{1, 2, 3}};

    ut_assert_eq(arr1[0], 1);
    ut_assert_eq(arr1[1], 2);
    ut_assert_eq(arr1[2], 3);
    ut_assert_eq(arr1.back(), 3);
    ut_assert_eq(&arr1.back(), arr1.data() + arr1.size() - 1);

    std::array<int, 3> arr2{1, 2, 3};
    ut_assert_eq(arr2[0], 1);
    ut_assert_eq(arr2[1], 2);
    ut_assert_eq(arr2[2], 3);
    ut_assert_eq(arr2.front(), 1);
    ut_assert_eq(&arr2.front(), arr2.data());
}

ut_test(iterators)
{
    std::array<int, 5> arr1{4, 3, 2, 1, 0};
    std::array<int, 5> arr2{0, 1, 2, 3, 4};

    auto it1 = arr1.cbegin();
    auto rit2 = arr2.crbegin();
    while (it1 != arr1.cend()) {
        ut_assert_eq(*it1, *rit2);
        ++it1;
        ++rit2;
    }
    ut_assert_eq(rit2, arr2.crend());

    std::array<int, 0> arr3{};
    ut_assert_eq(arr3.begin(), arr3.end());
}

ut_test(fill)
{
    std::array<int, 5> arr1{};

    arr1.fill(42);
    for (auto &&cur : arr1) {
        ut_assert_eq(cur, 42);
    }
}

ut_test(swap)
{
    std::array<int, 3> arr1{0, 1, 2};
    std::array<int, 3> arr2{2, 1, 0};

    std::swap(arr1, arr2);
}

ut_test(get)
{
    static constexpr std::array<int, 3> arr{0, 1, 2};

    static_assert(std::get<0>(arr) == 0);
    static_assert(&std::get<0>(arr) == arr.data() + 0);
    static_assert(std::get<1>(arr) == 1);
    static_assert(&std::get<1>(arr) == arr.data() + 1);
    static_assert(std::get<2>(arr) == 2);
    static_assert(&std::get<2>(arr) == arr.data() + 2);
}

ut_group(array,
         ut_get_test(size),
         ut_get_test(access),
         ut_get_test(iterators),
         ut_get_test(fill),
         ut_get_test(get)
);

void run_array_tests()
{
    ut_run_group(ut_get_group(array));
}

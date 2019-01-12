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

ut_test(minmax_element)
{
    int arr1[] = {1, 2, 1, 4, 5};

    auto[min1, max1] = std::minmax_element(std::begin(arr1), std::end(arr1));
    ut_assert_eq(min1, std::begin(arr1));
    ut_assert_eq(max1, std::begin(arr1) + 4);

    auto[min2, max2] = std::minmax_element(std::begin(arr1) + 1, std::begin(arr1) + 1);
    ut_assert_eq(min2, std::begin(arr1) + 1);
    ut_assert_eq(max2, std::begin(arr1) + 1);

    auto[min3, max3] = std::minmax_element(std::end(arr1), std::end(arr1));
    ut_assert_eq(min3, std::end(arr1));
    ut_assert_eq(max3, std::end(arr1));

    auto[min4, max4] = std::minmax_element(std::begin(arr1), std::end(arr1), [](const auto &a, const auto &b) {
        return -a < -b;
    });
    ut_assert_eq(min4, std::begin(arr1) + 4);
    ut_assert_eq(max4, std::begin(arr1) + 2); // Unlike max_element, minmax_element finds the last biggest element
}

ut_test(clamp)
{
    int i = 1;
    int j = 10;

    ut_assert_eq(std::clamp(42, i, j), j);
    ut_assert_eq(&std::clamp(42, i, j), &j);

    ut_assert_eq(std::clamp(0, i, j), i);
    ut_assert_eq(&std::clamp(0, i, j), &i);

    int k = 5;
    ut_assert_eq(std::clamp(k, i, j), k);
    ut_assert_eq(&std::clamp(k, i, j), &k);
}

namespace
{
    namespace tests
    {
        class not_swappable
        {
        public:
            explicit not_swappable(int data) noexcept : _data(data)
            {
            }

            not_swappable(const not_swappable &) noexcept = default;

            not_swappable &operator=(const not_swappable &) noexcept = default;

            not_swappable(not_swappable &&) noexcept = delete;

            not_swappable &operator=(not_swappable &&) noexcept = delete;

            int data() const
            {
                return _data;
            }

        private:
            int _data;
        };

        void swap(not_swappable &a, not_swappable &b)
        {
            auto tmp = a;

            a = b;
            b = tmp;
        }
    }
}

ut_test(swap)
{
    using std::swap;

    int a = 0;
    int b = 1;
    swap(a, b);
    ut_assert_eq(a, 1);
    ut_assert_eq(b, 0);

    tests::not_swappable nsa(0);
    tests::not_swappable nsb(1);
    swap(nsa, nsb);
    ut_assert_eq(nsa.data(), 1);
    ut_assert_eq(nsb.data(), 0);
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

ut_test(copy)
{
    int arr[5] = {1, 2, 3, 4, 5};
    int arr2[5];

    std::copy(std::begin(arr), std::end(arr), std::begin(arr2));
    std::size_t i = 0;
    for (const auto &cur : arr2) {
        ut_assert_eq(cur, arr[i++]);
    }
}

ut_test(copy_if)
{
    int arr1[] = {0, 1, 2, 3, 4, 5};
    int arr2[3] = {0};

    auto end_it = std::copy_if(std::begin(arr1), std::end(arr1), std::begin(arr2), [](const auto &a) {
        return a % 2 == 0;
    });
    ut_assert_eq(end_it, std::end(arr2));
    for (int i = 0; i < 3; ++i) {
        ut_assert_eq(arr2[i], 2 * i);
    }
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

ut_test(remove_if)
{
    int arr[] = {0, 1, 2, 3, 4, 5, 6, 7};
    int arr2[] = {0, 1, 2, 3, 4, 5, 6, 7};

    auto end_it = std::remove_if(std::begin(arr), std::end(arr), [](const auto &a) {
        return a % 2 != 0;
    });
    ut_assert_eq(end_it, std::begin(arr) + 4);
    for (int i = 0; i < 4; ++i) {
        ut_assert_eq(arr[i], 2 * i);
    }

    end_it = std::remove_if(std::begin(arr2), std::end(arr2), [](const auto &a) {
        return a % 2 == 0;
    });
    ut_assert_eq(end_it, std::begin(arr2) + 4);
    for (int i = 0; i < 4; ++i) {
        ut_assert_eq(arr2[i], 2 * i + 1);
    }
}

ut_test(rotate)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};

    auto it1 = std::rotate(std::begin(arr1), std::begin(arr1) + 2, std::end(arr1));
    ut_assert_eq(it1, std::begin(arr1) + (std::end(arr1) - (std::begin(arr1) + 2)));
    ut_assert_eq(arr1[0], 3);
    ut_assert_eq(arr1[1], 4);
    ut_assert_eq(arr1[2], 5);
    ut_assert_eq(arr1[3], 1);
    ut_assert_eq(arr1[4], 2);

    auto it2 = std::rotate(std::begin(arr2), std::begin(arr2) + 3, std::end(arr2));
    ut_assert_eq(it2, std::begin(arr2) + (std::end(arr2) - (std::begin(arr2) + 3)));
    ut_assert_eq(arr2[0], 4);
    ut_assert_eq(arr2[1], 5);
    ut_assert_eq(arr2[2], 1);
    ut_assert_eq(arr2[3], 2);
    ut_assert_eq(arr2[4], 3);
}

ut_test(fill)
{
    int arr1[5] = {0};

    std::fill(std::begin(arr1), std::end(arr1), 1);
    for (auto &&i : arr1) {
        ut_assert_eq(i, 1);
    }
}

ut_test(fill_n)
{
    int arr1[5] = {0};

    auto it = std::fill_n(std::begin(arr1), 5, 1);
    ut_assert_eq(it, std::end(arr1));
    for (auto &&i : arr1) {
        ut_assert_eq(i, 1);
    }
}

ut_test(generate)
{
    int arr1[5] = {0};

    std::generate(std::begin(arr1), std::end(arr1), []() {
        return 1;
    });
    for (auto &&i : arr1) {
        ut_assert_eq(i, 1);
    }
}

ut_test(generate_n)
{
    int arr1[5] = {0};

    auto it = std::generate_n(std::begin(arr1), 5, []() {
        return 1;
    });
    ut_assert_eq(it, std::end(arr1));
    for (auto &&i : arr1) {
        ut_assert_eq(i, 1);
    }
}

ut_test(reverse)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5, 6};

    std::reverse(std::begin(arr1), std::end(arr1));
    for (int i = 0; i < 5; ++i) {
        ut_assert_eq(arr1[i], 5 - i);
    }

    std::reverse(std::begin(arr2), std::end(arr2));
    for (int i = 0; i < 6; ++i) {
        ut_assert_eq(arr2[i], 6 - i);
    }
}

ut_test(unique)
{
    int arr[] = {1, 2, 2, 3, 4, 5, 5};

    auto end_it = std::unique(std::begin(arr), std::end(arr));
    int i = 1;
    for (auto it = std::begin(arr); it != end_it; ++it) {
        ut_assert_eq(i, *it);
        ++i;
    }
    ut_assert_eq(i, 6);
}

ut_test(replace_if)
{
    char hello[] = "hexxo worxd";

    std::replace(std::begin(hello), std::end(hello), 'x', 'l');
    ut_assert_streq(hello, "hello world");
}

ut_group(algorithm,
         ut_get_test(min_element),
         ut_get_test(max_element),
         ut_get_test(minmax_element),
         ut_get_test(clamp),
         ut_get_test(swap),
         ut_get_test(for_each),
         ut_get_test(find_if),
         ut_get_test(all_of),
         ut_get_test(any_of),
         ut_get_test(none_of),
         ut_get_test(copy),
         ut_get_test(copy_if),
         ut_get_test(transform),
         ut_get_test(remove_if),
         ut_get_test(rotate),
         ut_get_test(fill),
         ut_get_test(fill_n),
         ut_get_test(generate),
         ut_get_test(generate_n),
         ut_get_test(reverse),
         ut_get_test(unique),
         ut_get_test(replace_if)
);

void run_algorithm_tests()
{
    ut_run_group(ut_get_group(algorithm));
}

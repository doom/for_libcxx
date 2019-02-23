/*
** Created by doom on 18/10/18.
*/

#include <ut_config.h>
#include <iterator>

ut_test(iterator_traits_pointer)
{
    using ptr_traits = std::iterator_traits<int *>;

    static_assert(std::is_same_v<typename ptr_traits::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<typename ptr_traits::value_type, int>);
    static_assert(std::is_same_v<typename ptr_traits::reference, int &>);
    static_assert(std::is_same_v<typename ptr_traits::pointer, int *>);
    static_assert(std::is_same_v<typename ptr_traits::iterator_category, std::random_access_iterator_tag>);
}

ut_test(reverse_iterator)
{
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {5, 4, 3, 2, 1};

    auto it1 = std::begin(arr1);
    auto rit2 = std::rbegin(arr2);
    while (it1 != std::end(arr1)) {
        ut_assert_eq(*it1, *rit2);
        ++it1;
        ++rit2;
    }
    ut_assert_eq(rit2, std::rend(arr2));
}

ut_group(iterator,
         ut_get_test(iterator_traits_pointer),
         ut_get_test(reverse_iterator)
);

void run_iterator_tests()
{
    ut_run_group(ut_get_group(iterator));
}

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

ut_group(iterator,
         ut_get_test(iterator_traits_pointer)
);

void run_iterator_tests()
{
    ut_run_group(ut_get_group(iterator));
}

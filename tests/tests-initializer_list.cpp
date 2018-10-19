/*
** Created by doom on 18/10/18.
*/

#include <ut_config.h>
#include <initializer_list>
#include <type_traits>

ut_test(values)
{
    auto list = {0, 1, 2, 3, 4, 5};

    static_assert(std::is_same_v<decltype(list), std::initializer_list<int>>);
    int i = 0;
    for (const auto &cur : list) {
        ut_assert_eq(i, cur);
        ++i;
    }
}

ut_group(initializer_list,
         ut_get_test(values)
);

void run_initializer_list_tests()
{
    ut_run_group(ut_get_group(initializer_list));
}

/*
** Created by doom on 10/11/18.
*/

#include <ut_config.h>
#include <functional>
#include <type_traits>

ut_test(reference_wrapper)
{
    int i;
    auto ref = std::ref(i);
    static_assert(std::is_same_v<decltype(ref), std::reference_wrapper<int>>);
    ut_assert_eq(&i, &ref.get());
    ref.get() = 2;
    ut_assert_eq(i, 2);
    ++i;
    ut_assert_eq(i, ref.get());
}

ut_test(invoke)
{
    int i = 0;
    auto l1 = [](auto &&v) {
        v = 2;
    };

    std::invoke(l1, i);
    ut_assert_eq(i, 2);
}

ut_test(less)
{
    std::less<int> li;
    static_assert(li(1, 2));
    static_assert(!li(2, 1));
    static_assert(!li(2, 2));

    std::less<void> lv;
    static_assert(lv(1, 2));
    static_assert(!lv(2, 1));
    static_assert(!lv(2, 2));
}

ut_group(functional,
         ut_get_test(reference_wrapper),
         ut_get_test(invoke),
         ut_get_test(less)
);

void run_functional_tests()
{
    ut_run_group(ut_get_group(functional));
}

/*
** Created by doom on 11/10/18.
*/

#include <ut_config.h>
#include <utility>
#include <type_traits>

ut_test(move)
{
    int i = 1;

    static_assert(std::is_rvalue_reference_v<decltype(std::move(i))>);
}

static void dummy_function(const int &, int &&)
{
}

template <typename ...Args>
static void forwarding_function(Args &&...args)
{
    return dummy_function(std::forward<Args>(args)...);
}

ut_test(forward)
{
    int a = 1;
    int b = 2;

    forwarding_function(a, std::move(b));
}

ut_group(utility,
         ut_get_test(move),
         ut_get_test(forward)
);

void run_utility_tests()
{
    ut_run_group(ut_get_group(utility));
}

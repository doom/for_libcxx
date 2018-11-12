/*
** Created by doom on 11/11/18.
*/

#include <ut_config.h>
#include <memory>
#include <type_traits>

namespace
{
    struct overloading_addressof
    {
        int operator&()
        {
            return 2;
        }
    };
}

ut_test(addressof)
{
    int i = 0;
    ut_assert_eq(std::addressof(i), &i);

    overloading_addressof oa[1];
    ut_assert_eq(std::addressof(oa[0]), oa);
}

namespace
{
    template <typename T>
    struct fake_ptr
    {
        using difference_type = int;

        static auto pointer_to(int &x)
        {
            return fake_ptr{&x};
        }

        int *ptr;
    };
}

ut_test(pointer_traits)
{
    using intptr_traits = std::pointer_traits<int *>;

    static_assert(std::is_same_v<intptr_traits::pointer, int *>);
    static_assert(std::is_same_v<intptr_traits::element_type, int>);
    static_assert(std::is_same_v<intptr_traits::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<intptr_traits::rebind<char>, char *>);
    int i = 0;
    auto ptr = intptr_traits::pointer_to(i);
    ut_assert_eq(ptr, &i);

    using fakeptr_traits = std::pointer_traits<fake_ptr<int>>;
    static_assert(std::is_same_v<fakeptr_traits::pointer, fake_ptr<int>>);
    static_assert(std::is_same_v<fakeptr_traits::element_type, int>);
    static_assert(std::is_same_v<fakeptr_traits::difference_type, int>);
    static_assert(std::is_same_v<fakeptr_traits::rebind<char>, fake_ptr<char>>);
    auto ptr2 = fakeptr_traits::pointer_to(i);
    ut_assert_eq(ptr2.ptr, &i);
}

ut_group(memory,
         ut_get_test(addressof),
         ut_get_test(pointer_traits)
);

void run_memory_tests()
{
    ut_run_group(ut_get_group(memory));
}

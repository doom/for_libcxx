/*
** Created by doom on 11/11/18.
*/

#include <ut_config.h>
#include <memory>
#include <type_traits>
#include <limits>

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

namespace
{
    template <typename T>
    struct fake_allocator
    {
        using value_type = T;
        using difference_type = int;

        T *allocate(size_t)
        {
            return &i;
        }

        void deallocate(T *, size_t)
        {
        }

        T i;
    };
}

ut_test(allocator_traits)
{
    using alloc_trts = std::allocator_traits<fake_allocator<int>>;

    static_assert(std::is_same_v<alloc_trts::value_type, int>);
    static_assert(std::is_same_v<alloc_trts::pointer, int *>);
    static_assert(std::is_same_v<alloc_trts::const_pointer, const int *>);
    static_assert(std::is_same_v<alloc_trts::void_pointer, void *>);
    static_assert(std::is_same_v<alloc_trts::const_void_pointer, const void *>);
    static_assert(std::is_same_v<alloc_trts::difference_type, int>);
    static_assert(std::is_same_v<alloc_trts::size_type, unsigned int>);
    static_assert(alloc_trts::propagate_on_container_copy_assignment::value == false);
    static_assert(alloc_trts::propagate_on_container_move_assignment::value == false);
    static_assert(alloc_trts::propagate_on_container_swap::value == false);
    static_assert(alloc_trts::is_always_equal::value == false);

    fake_allocator<int> al;
    int *ptr = alloc_trts::allocate(al, 1, nullptr);
    alloc_trts::construct(al, ptr, 2);
    ut_assert_eq(*ptr, 2);
    alloc_trts::deallocate(al, ptr, 1);
    ut_assert_eq(alloc_trts::max_size(al), std::numeric_limits<alloc_trts::size_type>::max() / sizeof(alloc_trts::value_type));
    static_assert(std::is_same_v<alloc_trts::rebind_alloc<char>, fake_allocator<char>>);
    static_assert(std::is_same_v<alloc_trts::rebind_traits<char>, std::allocator_traits<fake_allocator<char>>>);
}

ut_group(memory,
         ut_get_test(addressof),
         ut_get_test(pointer_traits),
         ut_get_test(allocator_traits)
);

void run_memory_tests()
{
    ut_run_group(ut_get_group(memory));
}

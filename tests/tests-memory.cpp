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

    using default_trts = std::allocator_traits<std::allocator<int>>;
    static_assert(std::is_same_v<default_trts::value_type, int>);
    static_assert(std::is_same_v<default_trts::pointer, int *>);
    static_assert(std::is_same_v<default_trts::const_pointer, const int *>);
    static_assert(std::is_same_v<default_trts::void_pointer, void *>);
    static_assert(std::is_same_v<default_trts::const_void_pointer, const void *>);
    static_assert(std::is_same_v<default_trts::difference_type, std::ptrdiff_t>);
    static_assert(std::is_same_v<default_trts::size_type, std::size_t>);
    static_assert(default_trts::propagate_on_container_copy_assignment::value == false);
    static_assert(default_trts::propagate_on_container_move_assignment::value == true);
    static_assert(default_trts::propagate_on_container_swap::value == false);
    static_assert(default_trts::is_always_equal::value == true);

    std::allocator<int> al2;
    ut_assert_eq(default_trts::max_size(al2), std::numeric_limits<default_trts::size_type>::max() / sizeof(default_trts::value_type));
    static_assert(std::is_same_v<default_trts::rebind_alloc<char>, std::allocator<char>>);
    static_assert(std::is_same_v<default_trts::rebind_traits<char>, std::allocator_traits<std::allocator<char>>>);
}

namespace
{
    template <typename T>
    struct mark_deleter
    {
        void operator()(T *ptr)
        {
            last_deleted = ptr;
        }

        static T *last_deleted;
    };

    template <typename T>
    inline T *mark_deleter<T>::last_deleted = nullptr;

    template <typename T>
    struct do_nothing_deleter
    {
        void operator()(T *)
        {
        }
    };
}

ut_test(unique_ptr_move)
{
    static_assert(sizeof(std::unique_ptr<int *>) == sizeof(int *), "std::unique_ptr should use EBO when possible");

    int a = 2;
    {
        std::unique_ptr<int, mark_deleter<int>> a_ptr2;
        {
            std::unique_ptr<int, mark_deleter<int>> a_ptr(&a);

            a_ptr2 = std::move(a_ptr);
        }
        ut_assert_eq(mark_deleter<int>::last_deleted, nullptr); // move should reset a_ptr to nullptr
    }
    ut_assert_eq(mark_deleter<int>::last_deleted, &a);

    int b = 3;
    {
        std::unique_ptr<int, mark_deleter<int>> b_ptr(&b);
        {
            std::unique_ptr<int, mark_deleter<int>> a_ptr(&a);

            b_ptr = std::move(a_ptr);
        }
        ut_assert_eq(mark_deleter<int>::last_deleted, &b); // move should swap a_ptr and b_ptr
    }
    ut_assert_eq(mark_deleter<int>::last_deleted, &a);
}

ut_test(unique_ptr_comparison)
{
    std::unique_ptr<int, do_nothing_deleter<int>> ptr;

    ut_assert_eq(ptr, nullptr);
    ut_assert_eq(ptr, ptr);
    ut_assert_le(ptr, nullptr);
    ut_assert_le(nullptr, ptr);

    int a = 2;
    ptr.reset(&a);
    ut_assert_eq(ptr, ptr);
    ut_assert_ne(ptr, nullptr);
    ut_assert_gt(ptr, nullptr);
    ut_assert_ge(ptr, nullptr);
    ut_assert_ge(ptr, ptr);
    ut_assert_lt(nullptr, ptr);
    ut_assert_le(nullptr, ptr);
    ptr.reset();
}

ut_group(memory,
         ut_get_test(addressof),
         ut_get_test(pointer_traits),
         ut_get_test(allocator_traits),
         ut_get_test(unique_ptr_move),
         ut_get_test(unique_ptr_comparison),
);

void run_memory_tests()
{
    ut_run_group(ut_get_group(memory));
}

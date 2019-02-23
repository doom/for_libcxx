/*
** Created by doom on 12/11/18.
*/

#include <ut_config.h>
#include <vector>

namespace
{
    template <typename T>
    struct buffer_resource
    {
        using value_type = T;
        using pointer = value_type *;

        pointer allocate(size_t n)
        {
            auto ret = buffer + index;

            index += n * sizeof(T);
            return reinterpret_cast<pointer>(ret);
        }

        void deallocate(pointer p, size_t size)
        {
            if (!(std::begin(buffer) <= (char *)p && (char *)(p + size) <= buffer + index)) {
                ut_printf("Invalid free\n");
            }
            if ((char *)(p + size) == buffer + index) {
                index -= size * sizeof(T);
            }
        }

        alignas(T) char buffer[4096];
        size_t index{0};
    };

    template <typename T>
    static buffer_resource<T> buf_res;

    template <typename T>
    struct bump_allocator
    {
        using value_type = T;
        using pointer = value_type *;

        using propagate_on_container_move_assignment = std::true_type;

        pointer allocate(size_t n)
        {
            return buf_res<T>.allocate(n);
        }

        void deallocate(pointer p, size_t size)
        {
            buf_res<T>.deallocate(p, size);
        }

        friend bool operator==(const bump_allocator &lhs, const bump_allocator &rhs)
        {
            return &lhs == &rhs;
        }

        friend bool operator!=(const bump_allocator &lhs, const bump_allocator &rhs)
        {
            return !(rhs == lhs);
        }
    };
}

ut_test(basic)
{
    std::vector<int, bump_allocator<int>> vec;

    ut_assert(vec.empty());
    ut_assert_eq(vec.size(), 0u);
    ut_assert_eq(vec.capacity(), 0u);

    vec.push_back(1);
    ut_assert_false(vec.empty());
    ut_assert_eq(vec.size(), 1u);
    ut_assert_gt(vec.capacity(), 0u);
    ut_assert_eq(vec.front(), 1);
    ut_assert_eq(vec.back(), 1);

    vec.push_back(2);
    ut_assert_false(vec.empty());
    ut_assert_eq(vec.size(), 2u);
    ut_assert_gt(vec.capacity(), 0u);
    ut_assert_eq(vec.front(), 1);
    ut_assert_eq(vec.back(), 2);
}

namespace
{
    struct test_count
    {
        test_count(int i) noexcept: i(i)
        {
            ++nb_constructions;
        }

        ~test_count() noexcept
        {
            ++nb_destructions;
        }

        test_count(const test_count &other) noexcept : i(other.i)
        {
            ++nb_constructions;
        }

        test_count(test_count &&other) noexcept : i(other.i)
        {
            ++nb_constructions;
        }

        int i;


        static unsigned int nb_constructions;
        static unsigned int nb_destructions;

        static void reset() noexcept
        {
            nb_constructions = nb_destructions = 0;
        }
    };

    unsigned int test_count::nb_constructions{0};
    unsigned int test_count::nb_destructions{0};
}

ut_test(multiple_reallocation)
{
    std::vector<test_count, bump_allocator<test_count>> vec;

    test_count::reset();
    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }
    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec[i].i, i);
    }
    vec.clear();
    ut_assert_eq(test_count::nb_constructions, test_count::nb_destructions);
}

ut_test(single_preallocation)
{
    std::vector<test_count, bump_allocator<test_count>> vec;

    test_count::reset();
    vec.reserve(50);
    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }
    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec[i].i, i);
    }
    vec.clear();
    ut_assert_eq(test_count::nb_constructions, 50);
    ut_assert_eq(test_count::nb_destructions, 50);
}

ut_test(pop_back)
{
    std::vector<int, bump_allocator<int>> vec;

    vec.reserve(50);
    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }
    for (int i = 49; i >= 0; --i) {
        ut_assert_eq(vec.back(), i);
        vec.pop_back();
    }
}

ut_test(construct_with_fill)
{
    std::vector<int, bump_allocator<int>> vec(50, 23);

    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec[i], 23);
    }
}

ut_test(construct_with_default)
{
    std::vector<int, bump_allocator<int>> vec(50);

    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec[i], 0);
    }
}

ut_test(copy_constructor)
{
    std::vector<int, bump_allocator<int>> vec;

    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }

    std::vector<int, bump_allocator<int>> vec2 = vec;

    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec[i], i);
        ut_assert_eq(vec2[i], i);
    }
}

ut_test(move_constructor)
{
    std::vector<int, bump_allocator<int>> vec;

    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }

    std::vector<int, bump_allocator<int>> vec2 = std::move(vec);
    ut_assert(vec.empty());
    ut_assert_eq(vec.data(), nullptr);

    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec2[i], i);
    }
}

ut_test(move_constructor_with_allocator)
{
    std::vector<int, bump_allocator<int>> vec;

    for (int i = 0; i < 50; ++i) {
        vec.emplace_back(i);
    }

    std::vector<int, bump_allocator<int>> vec2(std::move(vec), bump_allocator<int>{});
    // vec does not have to be empty
    ut_assert_ne(vec.data(), vec2.data());

    for (int i = 0; i < 50; ++i) {
        ut_assert_eq(vec2[i], i);
    }
}

ut_test(move_assignment)
{
    std::vector<int, bump_allocator<int>> vec;

    vec.reserve(16);
    auto data_ptr = vec.data();
    ut_assert_eq(vec.capacity(), 16);
    for (int i = 0; i < 16; ++i) {
        vec.emplace_back(i);
    }

    std::vector<int, bump_allocator<int>> vec2;

    vec2 = std::move(vec);
    ut_assert(vec.empty());
    ut_assert_ne(vec.data(), data_ptr);
    ut_assert_eq(vec2.size(), 16);
    ut_assert_eq(vec2.data(), data_ptr);
    for (int i = 0; i < 16; ++i) {
        ut_assert_eq(vec2[i], i);
    }
}

ut_test(copy_assignment)
{
    std::vector<int, bump_allocator<int>> vec;

    vec.reserve(16);
    auto data_ptr = vec.data();
    ut_assert_eq(vec.capacity(), 16);
    for (int i = 0; i < 16; ++i) {
        vec.emplace_back(i);
    }

    std::vector<int, bump_allocator<int>> vec2;

    vec2 = vec;
    ut_assert_ge(vec.capacity(), 16);
    ut_assert_eq(vec.size(), 16);
    ut_assert_eq(vec.data(), data_ptr);
    ut_assert_ge(vec2.capacity(), 16);
    ut_assert_eq(vec2.size(), 16);
    ut_assert_ne(vec2.data(), data_ptr);
    for (int i = 0; i < 16; ++i) {
        ut_assert_eq(vec2[i], i);
        ut_assert_eq(vec[i], i);
    }
}

ut_test(insert_one)
{
    std::vector<int, bump_allocator<int>> vec;

    for (int i = 0; i < 16; ++i) {
        if (i != 3)
            vec.emplace_back(i);
    }

    vec.insert(vec.begin() + 3, 3);
    ut_assert_eq(vec.size(), 16);

    for (int i = 0; i < 16; ++i) {
        ut_assert_eq(vec[i], i);
    }
}

ut_test(initializer_list)
{
    std::vector<int, bump_allocator<int>> vec{0, 1, 2, 3, 4};

    ut_assert_eq(vec.size(), 5);
    ut_assert_ge(vec.capacity(), 5);
    for (int i = 0; i < 5; ++i) {
        ut_assert_eq(vec[i], i);
    }
}

ut_test(swap)
{
    std::vector<int, bump_allocator<int>> vec1{0, 1, 2, 3, 4};
    std::vector<int, bump_allocator<int>> vec2{4, 3, 2, 1, 0};
    auto data1 = vec1.data();
    auto data2 = vec2.data();

    std::swap(vec1, vec2);
    ut_assert_eq(vec1.data(), data2);
    ut_assert_eq(vec2.data(), data1);
    for (int i = 0; i < 5; ++i) {
        ut_assert_eq(vec1[i], 4 - i);
        ut_assert_eq(vec2[i], i);
    }
}

ut_group(vector,
         ut_get_test(basic),
         ut_get_test(multiple_reallocation),
         ut_get_test(single_preallocation),
         ut_get_test(pop_back),
         ut_get_test(construct_with_fill),
         ut_get_test(construct_with_default),
         ut_get_test(copy_constructor),
         ut_get_test(move_constructor),
         ut_get_test(move_constructor_with_allocator),
         ut_get_test(move_assignment),
         ut_get_test(copy_assignment),
         ut_get_test(insert_one),
         ut_get_test(initializer_list),
         ut_get_test(swap)
);

void run_vector_tests()
{
    ut_run_group(ut_get_group(vector));
}

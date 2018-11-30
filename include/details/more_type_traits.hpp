/*
** Created by doom on 21/11/18.
*/

#ifndef FOR_LIBCXX_MORE_TYPE_TRAITS_HPP
#define FOR_LIBCXX_MORE_TYPE_TRAITS_HPP

#include <type_traits>

namespace std::more
{
    namespace details
    {
        template <typename T>
        struct is_implicitly_default_constructible_helper
        {
            template <typename U>
            static void test2(const U &u);

            template <typename U = T, typename = decltype(test2<const U &>({}))>
            static std::true_type test(int);

            static std::false_type test(...);

            static constexpr const bool value = decltype(test(0))::value;
        };
    }

    template <typename T>
    struct is_implicitly_default_constructible :
        std::bool_constant<std::is_default_constructible_v<T>
                           && details::is_implicitly_default_constructible_helper<T>::value>
    {
    };

    template <typename T>
    inline constexpr const bool is_implicitly_default_constructible_v = is_implicitly_default_constructible<T>::value;

    template <bool value>
    using overload_n_if = std::enable_if_t<value, int>;

    namespace details
    {
        template <typename T>
        struct decay_ref_wrapper
        {
            using type = T;
        };

        template <typename T>
        struct decay_ref_wrapper<std::reference_wrapper<T>>
        {
            using type = T &;
        };
    }

    template <typename T>
    using decay_and_unwrap_ref_t = typename details::decay_ref_wrapper<std::decay_t<T>>::type;
}

#endif /* !FOR_LIBCXX_MORE_TYPE_TRAITS_HPP */

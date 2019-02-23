/*
** Created by doom on 22/02/19.
*/

#ifndef FOR_LIBCXX_DETAILS_ITERATOR_CONCEPT_CHECKS_HPP
#define FOR_LIBCXX_DETAILS_ITERATOR_CONCEPT_CHECKS_HPP

#include <iterator>
#include <type_traits>

namespace std::details
{
    template <typename T, typename = void>
    struct is_iterator : std::false_type
    {
    };

    template <typename T>
    struct is_iterator<T, std::void_t<typename std::iterator_traits<T>::iterator_category>> : std::true_type
    {
    };

    template <typename T>
    inline constexpr const bool is_iterator_v = is_iterator<T>::value;

    template <bool b>
    struct is_iterator_of_category_helper
    {
        template <typename, typename>
        using type = false_type;
    };

    template <>
    struct is_iterator_of_category_helper<true>
    {
        template <typename T, typename Tag>
        using type = std::is_convertible<typename std::iterator_traits<T>::iterator_category, Tag>;
    };

    template <typename T>
    using is_input_iterator = typename is_iterator_of_category_helper<is_iterator_v<T>>::template type<T, input_iterator_tag>;

    template <typename T>
    inline constexpr const bool is_input_iterator_v = is_input_iterator<T>::value;

    template <typename T>
    using is_bidirectional_iterator = typename is_iterator_of_category_helper<is_iterator_v<T>>::template type<T, std::bidirectional_iterator_tag>;

    template <typename T>
    inline constexpr const bool is_bidirectional_iterator_v = is_bidirectional_iterator<T>::value;

    template <typename T>
    using is_random_access_iterator = typename is_iterator_of_category_helper<is_iterator_v<T>>::template type<T, std::random_access_iterator_tag>;

    template <typename T>
    inline constexpr const bool is_random_access_iterator_v = is_random_access_iterator<T>::value;
}

#endif /* !FOR_LIBCXX_DETAILS_ITERATOR_CONCEPT_CHECKS_HPP */

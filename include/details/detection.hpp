/*
** Created by doom on 11/11/18.
*/

#ifndef FOR_LIBCXX_DETECTION_HPP
#define FOR_LIBCXX_DETECTION_HPP

#include <type_traits>

namespace std::details
{
    template <typename, template <typename ...> typename MetaF, typename ...Args>
    struct is_detected : std::false_type
    {
    };

    template <template <typename ...> typename MetaF, typename ...Args>
    struct is_detected<std::void_t<MetaF<Args...>>, MetaF, Args...> : std::true_type
    {
    };

    template <template <typename ...> typename MetaF, typename ...Params>
    inline constexpr bool is_detected_v = is_detected<void, MetaF, Params...>::value;

    template <typename, typename Fallback, template <typename ...> typename MetaF, typename ...Args>
    struct type_unless_detected
    {
        using type = Fallback;
    };

    template <typename Fallback, template <typename ...> typename MetaF, typename ...Args>
    struct type_unless_detected<std::void_t<MetaF<Args...>>, Fallback, MetaF, Args...>
    {
        using type = MetaF<Args...>;
    };

    template <typename Fallback, template <typename ...> typename MetaF, typename ...Params>
    using type_unless_detected_t = typename type_unless_detected<void, Fallback, MetaF, Params...>::type;
}

#endif /* !FOR_LIBCXX_DETECTION_HPP */

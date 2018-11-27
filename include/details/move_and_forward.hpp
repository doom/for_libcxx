/*
** Created by doom on 27/11/18.
*/

#ifndef FOR_LIBCXX_MOVE_AND_FORWARD_HPP
#define FOR_LIBCXX_MOVE_AND_FORWARD_HPP

#include <type_traits>

namespace std
{
    template <typename T>
    constexpr remove_reference_t<T> &&move(T &&t)
    {
        return static_cast<remove_reference_t<T> &&>(t);
    }

    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &t)
    {
        return static_cast<T &&>(t);
    }

    template <typename T>
    constexpr T &&forward(remove_reference_t<T> &&t)
    {
        return static_cast<T &&>(t);
    }
}

#endif /* !FOR_LIBCXX_MOVE_AND_FORWARD_HPP */

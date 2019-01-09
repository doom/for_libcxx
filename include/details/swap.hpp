/*
** Created by doom on 08/01/19.
*/

#ifndef FOR_LIBCXX_DETAILS_SWAP_HPP
#define FOR_LIBCXX_DETAILS_SWAP_HPP

#include <type_traits>
#include <details/move_and_forward.hpp>

namespace std
{
    template <typename T, typename = std::enable_if_t<std::is_move_constructible_v<T> && std::is_move_assignable_v<T>>>
    void swap(T &a, T &b) noexcept(noexcept(std::is_nothrow_move_constructible<T>::value &&
                                            std::is_nothrow_move_assignable<T>::value))
    {
        T tmp(std::move(a));

        a = std::move(b);
        b = std::move(tmp);
    }
}

#endif /* !FOR_LIBCXX_DETAILS_SWAP_HPP */

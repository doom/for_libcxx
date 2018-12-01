/*
** Created by doom on 01/12/18.
*/

#ifndef FOR_LIBCXX_ADDRESSOF_HPP
#define FOR_LIBCXX_ADDRESSOF_HPP

namespace std
{
    template <typename T>
    T *addressof(T &arg) noexcept
    {
        return reinterpret_cast<T *>(&const_cast<char &>(reinterpret_cast<const volatile char &>(arg)));
    }

    template <typename T>
    const T *addressof(const T &&arg) noexcept = delete;
}

#endif /* !FOR_LIBCXX_ADDRESSOF_HPP */

/*
** Created by doom on 20/10/18.
*/

#ifndef FOR_LIBCXX_CHAR_TRAITS_HPP
#define FOR_LIBCXX_CHAR_TRAITS_HPP

#include <cstddef>
#include <string.h>
#include "constexpr_cstring.hpp"

namespace std
{
    template <typename CharT>
    struct char_traits
    {
        /** Empty trait, should be specialized */
    };

    namespace details
    {
        template <typename T>
        inline constexpr bool is_constant_array(const T *ptr, size_t n) noexcept
        {
            while (n--) {
                if (!__builtin_constant_p(*ptr))
                    return false;
                ++ptr;
            }
            return true;
        }

        inline constexpr bool is_constant_cstring(const char *ptr) noexcept
        {
            while (__builtin_constant_p(*ptr) && *ptr != '\0')
                ++ptr;
            return __builtin_constant_p(*ptr);
        }
    }

#define is_constant_value(x)        __builtin_constant_p(x)
#define is_constant_array(p, n)     details::is_constant_array(p, n)
#define is_constant_cstring(s)      details::is_constant_cstring(s)

    template <>
    struct char_traits<char>
    {
        using char_type = char;
        using int_type = int;
        using pos_type = size_t;
        using off_type = size_t;
        using state_type = void; /** Not supported yet */

        static constexpr void assign(char_type &to, const char_type &from) noexcept
        {
            to = from;
        }

        static char_type *assign(char_type *s, size_t n, char_type c)
        {
            return (char_type *)memset(s, c, n);
        }

        static constexpr bool eq(const char_type &c1, const char_type &c2) noexcept
        {
            return c1 == c2;
        }

        static constexpr bool lt(const char_type &c1, const char_type &c2) noexcept
        {
            return static_cast<unsigned char>(c1) < static_cast<unsigned char>(c2);
        }

        static char_type *move(char_type *dest, const char_type *src, size_t n) noexcept
        {
            return (char_type *)memmove(dest, src, n);
        }

        static char_type *copy(char_type *dest, const char_type *src, size_t n) noexcept
        {
            return (char_type *)memcpy(dest, src, n);
        }

        /** Since C++17, these functions are constexpr, so we need compiler builtins */

        static constexpr int compare(const char_type *s1, const char_type *s2, size_t n) noexcept
        {
            if constexpr (is_constant_value(n) && is_constant_array(s1, n) && is_constant_array(s2, n)) {
                return details::constexpr_memcmp(s1, s2, n);
            }
            return __builtin_memcmp(s1, s2, n);
        }

        static constexpr size_t length(const char_type *str) noexcept
        {
            if (is_constant_cstring(str)) {
                return details::constexpr_strlen(str);
            }
            return __builtin_strlen(str);
        }

        static constexpr const char_type *find(const char_type *p, size_t n, const char_type &ch)
        {
            if constexpr (is_constant_value(n) && is_constant_value(ch) && is_constant_array(p, n)) {
                return (const char_type *)details::constexpr_memchr(p, ch, n);
            }
            return (const char_type *)__builtin_memchr(p, ch, n);
        }

        static constexpr char_type to_char_type(int_type i) noexcept
        {
            return static_cast<char_type>(i);
        }

        static constexpr int_type to_int_type(char_type c) noexcept
        {
            return static_cast<int_type>(static_cast<unsigned char>(c));
        }

        static constexpr bool eq_int_type(int_type i1, int_type i2) noexcept
        {
            return i1 == i2;
        }

        static constexpr int_type eof() noexcept
        {
            return -1;
        }

        static constexpr int_type not_eof(int_type i) noexcept
        {
            if (i != eof())
                return i;
            return 0;
        }
    };

#undef is_constant_cstring
#undef is_constant_array
#undef is_constant_value
}

#endif /* !FOR_LIBCXX_CHAR_TRAITS_HPP */

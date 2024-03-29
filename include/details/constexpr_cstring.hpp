/*
** Created by doom on 20/10/18.
*/

#ifndef FOR_LIBCXX_CONSTEXPR_CSTRING_HPP
#define FOR_LIBCXX_CONSTEXPR_CSTRING_HPP

#include <cstddef>

namespace std::details
{
    template <typename CharT>
    inline constexpr int constexpr_memcmp(const CharT *s1, const CharT *s2, size_t n) noexcept
    {
        while (n--) {
            if (*s1 < *s2)
                return -1;
            if (*s2 < *s1)
                return 1;
            ++s1;
            ++s2;
        }
        return 0;
    }

    inline constexpr size_t constexpr_strlen(const char *str) noexcept
    {
        const char *cur = str;

        while (*cur) {
            ++cur;
        }
        return cur - str;
    }

    template <typename CharT>
    inline constexpr const CharT *constexpr_memchr(const CharT *p, int c, size_t n) noexcept
    {
        while (n--) {
            if ((unsigned char)*p == c)
                return p;
            ++p;
        }
        return nullptr;
    }
}

#endif /* !FOR_LIBCXX_CONSTEXPR_CSTRING_HPP */

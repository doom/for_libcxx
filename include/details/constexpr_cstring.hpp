/*
** Created by doom on 20/10/18.
*/

#ifndef FOR_LIBCXX_CONSTEXPR_CSTRING_HPP
#define FOR_LIBCXX_CONSTEXPR_CSTRING_HPP

#include <cstddef>

namespace std::details
{
    inline constexpr int constexpr_memcmp(const void *p1, const void *p2, size_t n) noexcept
    {
        const auto *s1 = static_cast<const unsigned char *>(p1);
        const auto *s2 = static_cast<const unsigned char *>(p2);

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

    inline constexpr void *constexpr_memchr(const void *p, int c, size_t n) noexcept
    {
        const auto *s = static_cast<const unsigned char *>(p);

        while (n--) {
            if (*s == c)
                return (void *)s;
            ++s;
        }
        return nullptr;
    }
}

#endif /* !FOR_LIBCXX_CONSTEXPR_CSTRING_HPP */

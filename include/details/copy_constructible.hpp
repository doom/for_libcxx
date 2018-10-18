/*
** Created by doom on 15/10/18.
*/

#ifndef FOR_LIBCXX_NON_COPYABLE_HPP
#define FOR_LIBCXX_NON_COPYABLE_HPP

namespace std::details
{
    struct not_copy_constructible
    {
        not_copy_constructible() = default;

        not_copy_constructible(not_copy_constructible &&) noexcept = default;

        not_copy_constructible(const not_copy_constructible &) = delete;

        not_copy_constructible &operator=(not_copy_constructible &&) noexcept = default;

        not_copy_constructible &operator=(const not_copy_constructible &) = default;
    };

    template <bool cond>
    struct copy_constructible_if
    {
    };

    template <>
    struct copy_constructible_if<false> : not_copy_constructible
    {
    };
}

#endif /* !FOR_LIBCXX_NON_COPYABLE_HPP */

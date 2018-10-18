/*
** Created by doom on 16/10/18.
*/

#ifndef FOR_LIBCXX_COPY_ASSIGNABLE_HPP
#define FOR_LIBCXX_COPY_ASSIGNABLE_HPP

namespace std::details
{
    struct not_copy_assignable
    {
        not_copy_assignable() = default;

        not_copy_assignable(not_copy_assignable &&) noexcept = default;

        not_copy_assignable(const not_copy_assignable &) = default;

        not_copy_assignable &operator=(not_copy_assignable &&) noexcept = default;

        not_copy_assignable &operator=(const not_copy_assignable &) = delete;
    };

    template <bool cond>
    struct copy_assignable_if
    {
    };

    template <>
    struct copy_assignable_if<false> : not_copy_assignable
    {
    };
}

#endif /* !FOR_LIBCXX_COPY_ASSIGNABLE_HPP */

/*
** Created by doom on 16/10/18.
*/

#ifndef FOR_LIBCXX_MOVE_ASSIGNABLE_HPP
#define FOR_LIBCXX_MOVE_ASSIGNABLE_HPP

namespace std::details
{
    struct not_move_assignable
    {
        not_move_assignable() = default;

        not_move_assignable(not_move_assignable &&) noexcept = default;

        not_move_assignable(const not_move_assignable &) = default;

        not_move_assignable &operator=(not_move_assignable &&) noexcept = delete;

        not_move_assignable &operator=(const not_move_assignable &) = default;
    };

    template <bool cond>
    struct move_assignable_if
    {
    };

    template <>
    struct move_assignable_if<false> : not_move_assignable
    {
    };
}

#endif /* !FOR_LIBCXX_MOVE_ASSIGNABLE_HPP */

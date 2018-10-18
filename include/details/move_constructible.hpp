/*
** Created by doom on 15/10/18.
*/

#ifndef FOR_LIBCXX_NON_MOVABLE_HPP
#define FOR_LIBCXX_NON_MOVABLE_HPP

namespace std::details
{
    struct not_move_constructible
    {
        not_move_constructible() = default;

        not_move_constructible(not_move_constructible &&) noexcept = delete;

        not_move_constructible(const not_move_constructible &) = default;

        not_move_constructible &operator=(not_move_constructible &&) noexcept = default;

        not_move_constructible &operator=(const not_move_constructible &) = default;
    };

    template <bool cond>
    struct move_constructible_if
    {
    };

    template <>
    struct move_constructible_if<false> : not_move_constructible
    {
    };
}

#endif /* !FOR_LIBCXX_NON_MOVABLE_HPP */

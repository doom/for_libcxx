/*
** Created by doom on 04/03/19.
*/

#ifndef FOR_LIBCXX_DETAILS_CTOR_AND_ASSIGN_HELPERS_HPP
#define FOR_LIBCXX_DETAILS_CTOR_AND_ASSIGN_HELPERS_HPP

namespace std::details
{
    template <typename T, bool>
    class allow_move_construction_if : public T
    {
    public:
        using T::T;

        constexpr allow_move_construction_if() = default;

        allow_move_construction_if(const allow_move_construction_if &) = default;

        allow_move_construction_if(allow_move_construction_if &&) = default;

        allow_move_construction_if &operator=(const allow_move_construction_if &) = default;

        allow_move_construction_if &operator=(allow_move_construction_if &&) = default;
    };

    template <typename T>
    class allow_move_construction_if<T, false> : public T
    {
    public:
        using T::T;

        constexpr allow_move_construction_if() = default;

        allow_move_construction_if(const allow_move_construction_if &) = default;

        allow_move_construction_if(allow_move_construction_if &&) = delete;

        allow_move_construction_if &operator=(const allow_move_construction_if &) = default;

        allow_move_construction_if &operator=(allow_move_construction_if &&) = default;
    };

    template <typename T, bool>
    class allow_copy_construction_if : public T
    {
    public:
        using T::T;

        constexpr allow_copy_construction_if() = default;

        allow_copy_construction_if(const allow_copy_construction_if &) = default;

        allow_copy_construction_if(allow_copy_construction_if &&) = default;

        allow_copy_construction_if &operator=(const allow_copy_construction_if &) = default;

        allow_copy_construction_if &operator=(allow_copy_construction_if &&) = default;
    };

    template <typename T>
    class allow_copy_construction_if<T, false> : public T
    {
    public:
        using T::T;

        constexpr allow_copy_construction_if() = default;

        allow_copy_construction_if(const allow_copy_construction_if &) = delete;

        allow_copy_construction_if(allow_copy_construction_if &&) = default;

        allow_copy_construction_if &operator=(const allow_copy_construction_if &) = default;

        allow_copy_construction_if &operator=(allow_copy_construction_if &&) = default;
    };

    template <typename T, bool>
    class allow_move_assign_if : public T
    {
    public:
        using T::T;

        constexpr allow_move_assign_if() = default;

        allow_move_assign_if(const allow_move_assign_if &) = default;

        allow_move_assign_if(allow_move_assign_if &&) = default;

        allow_move_assign_if &operator=(const allow_move_assign_if &) = default;

        allow_move_assign_if &operator=(allow_move_assign_if &&) = default;
    };

    template <typename T>
    class allow_move_assign_if<T, false> : public T
    {
    public:
        using T::T;

        constexpr allow_move_assign_if() = default;

        allow_move_assign_if(const allow_move_assign_if &) = default;

        allow_move_assign_if(allow_move_assign_if &&) = default;

        allow_move_assign_if &operator=(const allow_move_assign_if &) = default;

        allow_move_assign_if &operator=(allow_move_assign_if &&) = delete;
    };

    template <typename T, bool>
    class allow_copy_assign_if : public T
    {
    public:
        using T::T;

        constexpr allow_copy_assign_if() = default;

        allow_copy_assign_if(const allow_copy_assign_if &) = default;

        allow_copy_assign_if(allow_copy_assign_if &&) = default;

        allow_copy_assign_if &operator=(const allow_copy_assign_if &) = default;

        allow_copy_assign_if &operator=(allow_copy_assign_if &&) = default;
    };

    template <typename T>
    class allow_copy_assign_if<T, false> : public T
    {
    public:
        using T::T;

        constexpr allow_copy_assign_if() = default;

        allow_copy_assign_if(const allow_copy_assign_if &) = default;

        allow_copy_assign_if(allow_copy_assign_if &&) = default;

        allow_copy_assign_if &operator=(const allow_copy_assign_if &) = delete;

        allow_copy_assign_if &operator=(allow_copy_assign_if &&) = default;
    };

    template <
        typename T,
        bool AllowCopyConstruction,
        bool AllowMoveConstruction,
        bool AllowCopyAssignment,
        bool AllowMoveAssignment
    >
    class allow_copy_and_move_if : public allow_copy_assign_if<
        allow_move_assign_if<
            allow_copy_construction_if<
                allow_move_construction_if<
                    T, AllowMoveConstruction
                >, AllowCopyConstruction
            >, AllowMoveAssignment
        >, AllowCopyAssignment
    >
    {
    public:
        using allow_copy_assign_if<
            allow_move_assign_if<
                allow_copy_construction_if<
                    allow_move_construction_if<
                        T, AllowMoveConstruction
                    >, AllowCopyConstruction
                >, AllowMoveAssignment
            >, AllowCopyAssignment>::allow_copy_assign_if;

        constexpr allow_copy_and_move_if() = default;
    };
}

#endif /* !FOR_LIBCXX_DETAILS_CTOR_AND_ASSIGN_HELPERS_HPP */

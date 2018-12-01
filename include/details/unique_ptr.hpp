/*
** Created by doom on 01/12/18.
*/

#ifndef FOR_LIBCXX_UNIQUE_PTR_HPP
#define FOR_LIBCXX_UNIQUE_PTR_HPP

#include <type_traits>
#include <utility>
#include <cstdint>
#include <stdbool.h>
#include <functional>

namespace std
{
    template <typename T>
    struct default_delete
    {
        constexpr default_delete() noexcept = default;

        template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
        default_delete(const default_delete<U> &) noexcept
        {
        }

        void operator()(T *ptr) const
        {
            static_assert(sizeof(T), "unable to delete a pointer to an incomplete type");
            delete ptr;
        }
    };

    template <typename T>
    struct default_delete<T[]>
    {
        constexpr default_delete() noexcept = default;

        template <typename U, typename = std::enable_if_t<std::is_convertible_v<U(*)[], T(*)[]>>>
        default_delete(const default_delete<U> &) noexcept
        {
        }

        template <typename U, typename = std::enable_if_t<std::is_convertible_v<U *, T *>>>
        void operator()(U *ptr) const
        {
            static_assert(sizeof(T), "unable to delete a pointer to an incomplete type");
            delete[] ptr;
        }
    };

    namespace details
    {
        template <typename Deleter, bool = std::is_empty_v<Deleter>>
        struct deleter_holder
        {
            Deleter _del;

            template <typename ...Args>
            deleter_holder(Args &&...args) noexcept : _del(std::forward<Args>(args)...)
            {
            }

            Deleter &get_deleter() & noexcept
            {
                return _del;
            }

            const Deleter &get_deleter() const & noexcept
            {
                return _del;
            }

            Deleter &&get_deleter() && noexcept
            {
                return std::move(_del);
            }

            const Deleter &&get_deleter() const && noexcept
            {
                return std::move(_del);
            }
        };

        template <typename Deleter>
        struct deleter_holder<Deleter, true> : Deleter
        {
            template <typename ...Args>
            deleter_holder(Args &&...args) noexcept : Deleter(std::forward<Args>(args)...)
            {
            }

            Deleter &get_deleter() &noexcept
            {
                return static_cast<Deleter &>(*this);
            }

            const Deleter &get_deleter() const & noexcept
            {
                return static_cast<const Deleter &>(*this);
            }

            Deleter &&get_deleter() && noexcept
            {
                return static_cast<Deleter &&>(*this);
            }

            const Deleter &&get_deleter() const && noexcept
            {
                return static_cast<const Deleter &&>(*this);
            }
        };
    }

    template <typename T, typename Deleter = std::default_delete<T>>
    class unique_ptr : details::deleter_holder<Deleter>
    {
    public:
        using pointer = T *;
        using element_type = T;
        using deleter_type = Deleter;

        using base = details::deleter_holder<Deleter>;

    private:
        pointer _p;

    public:
        constexpr unique_ptr() noexcept : _p(nullptr)
        {
        }

        constexpr unique_ptr(nullptr_t) noexcept : unique_ptr()
        {
        }

        explicit unique_ptr(pointer p) noexcept : _p(p)
        {
        }

        unique_ptr(pointer p,
                   std::conditional_t<std::is_reference_v<deleter_type>, deleter_type, const deleter_type &> d)
        noexcept : base(d), _p(p)
        {
        }

        unique_ptr(pointer p, std::remove_reference_t<deleter_type> &&d) noexcept : base(d), _p(p)
        {
        }

        unique_ptr(unique_ptr &&other) noexcept : base(std::forward<deleter_type>(other.get_deleter())),
                                                  _p(other.release())
        {
        }

        template <typename OtherType, typename OtherDeleter,
            typename = std::enable_if_t<
                std::is_convertible_v<typename unique_ptr<OtherType, OtherDeleter>::pointer, pointer>
                && std::conditional_t<
                    std::is_reference_v<deleter_type>,
                    std::is_same<deleter_type, OtherDeleter>,
                    std::is_convertible<OtherDeleter, deleter_type>
                >::value
            >
        >
        unique_ptr(unique_ptr<OtherType, OtherDeleter> &&other) noexcept :
            base(std::forward<OtherDeleter>(other.get_deleter())), _p(other.release())
        {
        }

        ~unique_ptr() noexcept
        {
            if (_p != nullptr) {
                get_deleter()(_p);
            }
        }

        unique_ptr &operator=(unique_ptr &&r) noexcept
        {
            reset(r.release());
            get_deleter() = std::forward<deleter_type>(r.get_deleter());
            return *this;
        }

        template <typename OtherType, typename OtherDeleter,
            typename = std::enable_if_t<
                std::is_convertible_v<typename unique_ptr<OtherType, OtherDeleter>::pointer, pointer>
                && std::is_assignable_v<deleter_type, OtherDeleter>
            >
        >
        unique_ptr &operator=(unique_ptr<OtherType, OtherDeleter> &&r) noexcept
        {
            reset(r.release());
            get_deleter() = std::forward<OtherDeleter>(r.get_deleter());
            return *this;
        }

        unique_ptr &operator=(nullptr_t) noexcept
        {
            reset();
            return *this;
        }

        unique_ptr(const unique_ptr &) = delete;

        unique_ptr &operator=(const unique_ptr &) = delete;

        using base::get_deleter;

        pointer get() const noexcept
        {
            return _p;
        }

        std::add_lvalue_reference_t<T> operator*() const
        {
            return *get();
        }

        pointer operator->() const noexcept
        {
            return get();
        }

        pointer release() noexcept
        {
            auto ptr = get();
            _p = pointer();
            return ptr;
        }

        void reset(pointer ptr = pointer()) noexcept
        {
            using std::swap;
            swap(_p, ptr);
            if (ptr != pointer()) {
                get_deleter()(ptr);
            }
        }

        void swap(unique_ptr &other) noexcept
        {
            using std::swap;
            swap(_p, other._p);
            swap(get_deleter(), other.get_deleter());
        }

        explicit operator bool() const noexcept
        {
            return get() != nullptr;
        }
    };

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator==(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return x.get() == y.get();
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator!=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return !(x == y);
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator<(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return (uintptr_t)x.get() < (uintptr_t)y.get(); //sorry
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator<=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return !(y < x);
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator>(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return y < x;
    }

    template <typename T1, typename D1, typename T2, typename D2>
    bool operator>=(const unique_ptr<T1, D1> &x, const unique_ptr<T2, D2> &y)
    {
        return !(x < y);
    }

    template <typename T, typename D>
    bool operator==(const unique_ptr<T, D> &x, nullptr_t) noexcept
    {
        return !x;
    }

    template <typename T, typename D>
    bool operator==(nullptr_t, const unique_ptr<T, D> &x) noexcept
    {
        return !x;
    }

    template <typename T, typename D>
    bool operator!=(const unique_ptr<T, D> &x, nullptr_t) noexcept
    {
        return bool(x);
    }

    template <typename T, typename D>
    bool operator!=(nullptr_t, const unique_ptr<T, D> &x) noexcept
    {
        return bool(x);
    }

    template <typename T, typename D>
    bool operator<(const unique_ptr<T, D> &x, nullptr_t)
    {
        return std::less<typename unique_ptr<T, D>::pointer>()(x.get(), nullptr);
    }

    template <typename T, typename D>
    bool operator<(nullptr_t, const unique_ptr<T, D> &y)
    {
        return std::less<typename unique_ptr<T, D>::pointer>()(nullptr, y.get());
    }

    template <typename T, typename D>
    bool operator<=(const unique_ptr<T, D> &x, nullptr_t)
    {
        return !(nullptr < x);
    }

    template <typename T, typename D>
    bool operator<=(nullptr_t, const unique_ptr<T, D> &y)
    {
        return !(y < nullptr);
    }

    template <typename T, typename D>
    bool operator>(const unique_ptr<T, D> &x, nullptr_t)
    {
        return nullptr < x;
    }

    template <typename T, typename D>
    bool operator>(nullptr_t, const unique_ptr<T, D> &y)
    {
        return y < nullptr;
    }

    template <typename T, typename D>
    bool operator>=(const unique_ptr<T, D> &x, nullptr_t)
    {
        return !(x < nullptr);
    }

    template <typename T, typename D>
    bool operator>=(nullptr_t, const unique_ptr<T, D> &y)
    {
        return !(nullptr < y);
    }

    template <typename T, typename ...Args>
    unique_ptr<T> make_unique(Args &&...args)
    {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

#endif /* !FOR_LIBCXX_UNIQUE_PTR_HPP */

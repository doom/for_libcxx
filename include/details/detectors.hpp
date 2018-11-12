/*
** Created by doom on 11/11/18.
*/

#ifndef FOR_LIBCXX_DETECTORS_HPP
#define FOR_LIBCXX_DETECTORS_HPP

namespace std
{
    template <typename T>
    T &&declval() noexcept;
}

namespace std::details
{
    template <typename T>
    using member_detector_element_type = typename T::element_type;

    template <typename T>
    using member_detector_difference_type = typename T::difference_type;

    template <typename T>
    using member_detector_size_type = typename T::size_type;

    template <typename T>
    using member_detector_value_type = typename T::value_type;

    template <typename T>
    using member_detector_pointer = typename T::pointer;

    template <typename T>
    using member_detector_const_pointer = typename T::const_pointer;

    template <typename T>
    using member_detector_void_pointer = typename T::void_pointer;

    template <typename T>
    using member_detector_const_void_pointer = typename T::const_void_pointer;

    template <typename T>
    using member_detector_propagate_on_container_copy_assignment = typename T::propagate_on_container_copy_assignment;

    template <typename T>
    using member_detector_propagate_on_container_move_assignment = typename T::propagate_on_container_move_assignment;

    template <typename T>
    using member_detector_propagate_on_container_swap = typename T::propagate_on_container_swap;

    template <typename T>
    using member_detector_is_always_equal = typename T::is_always_equal;

    template <typename T, typename ...Args>
    using member_func_detector_allocate = decltype(std::declval<T &>().allocate(std::declval<Args>()...));

    template <typename T, typename ...Args>
    using member_func_detector_construct = decltype(std::declval<T &>().construct(std::declval<Args>()...));

    template <typename T, typename ...Args>
    using member_func_detector_destroy = decltype(std::declval<T &>().destroy(std::declval<Args>()...));

    template <typename T, typename ...Args>
    using member_func_detector_select_on_container_copy_construction = decltype(std::declval<T &>().select_on_container_copy_construction(std::declval<Args>()...));

    template <typename T, typename ...Args>
    using member_func_detector_max_size = decltype(std::declval<T &>().max_size(std::declval<Args>()...));
}

#endif /* !FOR_LIBCXX_DETECTORS_HPP */

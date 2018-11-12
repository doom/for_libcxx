/*
** Created by doom on 11/11/18.
*/

#ifndef FOR_LIBCXX_DETECTORS_HPP
#define FOR_LIBCXX_DETECTORS_HPP

namespace std::details
{
    template <typename T>
    using member_detector_element_type = typename T::element_type;

    template <typename T>
    using member_detector_difference_type = typename T::difference_type;
}

#endif /* !FOR_LIBCXX_DETECTORS_HPP */

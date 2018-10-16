cmake_minimum_required(VERSION 3.9)

project(for_libcxx)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -Wextra -nostdlib -nostdinc -fno-builtin -fno-rtti -fno-exceptions -O3 -DFOR_LIBCXX_NO_EXCEPTIONS")

add_subdirectory(lib/for_libc)

set(LIBCXX_SOURCES
        include/details/config.hpp
        include/cstdint
        include/cstddef
        include/exception
        include/type_traits
        include/utility
        include/new
        src/dummy/dummy.cpp
        )

add_library(for_libcxx SHARED ${LIBCXX_SOURCES})
add_library(for_libcxx-static STATIC ${LIBCXX_SOURCES})

target_include_directories(for_libcxx SYSTEM PUBLIC include)
target_include_directories(for_libcxx-static SYSTEM PUBLIC include)

target_link_libraries(for_libcxx-static for_libc-static)

add_executable(for_libcxx-tests
        tests/tests-main.cpp
        tests/tests-type_traits.cpp
        tests/tests-utility.cpp
        )

set_target_properties(for_libcxx-tests PROPERTIES COMPILE_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions")

target_link_libraries(for_libcxx-tests for_libcxx-static ut)

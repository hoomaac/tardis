cmake_minimum_required(VERSION 3.22)

if (NOT CMAKE_HOST_UNIX)
    message(FATAL_ERROR "Only Linux supported")
endif()

set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "cmake toolchain file")

project(tardis-project)

add_subdirectory(flatbuf)
add_subdirectory(lib)
add_subdirectory(src tardis)

cmake_minimum_required(VERSION 3.22)

if (NOT CMAKE_HOST_UNIX)
    message(FATAL_ERROR "Only Linux supported")
endif()

option(CHECK_CPPLINT "Enable cpplint" ON)
option(LOCAL_INSTALL "install in the local directory for test purpose" ON)
set(ENCRYPTION true)

if (NOT CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "cmake toolchain file")
endif()

if (CHECK_CPPLINT)
    message(STATUS "cpplint is enabled")

    set(ALL_FILES)
    file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/lib/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
    file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

    list(APPEND ALL_FILES ${CPP_FILES} ${HEADER_FILES})

    find_program(CPP_LINT cpplint)
    message(STATUS "cpplint: " ${CPP_LINT})

    if (NOT CPP_LINT)
        message(SEND_ERROR "Cannot find cpplint!")
    endif()

    set(CPPLINT_FILTERS --filter=-whitespace/braces,-build/include_order)
    set(CPPLINT_LINE_LENGTH --linelength=120)

    add_custom_target(cpplint COMMAND ${CPP_LINT} ${CPPLINT_FILTERS} ${CPPLINT_LINE_LENGTH} ${ALL_FILES})
    
endif()

project(tardis-project)

# include standard gnu directory path
include(GNUInstallDirs)

#include config and include path of the project
include_directories(include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# config.h.in variables
set(HAVE_ENCRYPTION ${ENCRYPTION})

# compiler options
add_compile_options(-Wall -Wextra -Wredundant-tags)

add_subdirectory(flatbuf)
add_subdirectory(lib)
add_subdirectory(src tardis)

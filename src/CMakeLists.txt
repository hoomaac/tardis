cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "tardis")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

find_package(spdlog CONFIG REQUIRED)
find_package(zstd CONFIG REQUIRED)

# config.h.in variable
if (LOCAL_INSTALL)
    set(PREFIX_INSTALL_PATH ${CMAKE_BINARY_DIR}/)
else()
    set(PREFIX_INSTALL_PATH ${CMAKE_INSTALL_BINDIR}/)
endif()

set(INSTALL_PATH ${PREFIX_INSTALL_PATH}bin)
set(LOG_PATH ${PREFIX_INSTALL_PATH}log/${PROJECT_NAME}/${PROJECT_NAME}.log)

# copy and replace some variables inside of config file
configure_file(${CMAKE_SOURCE_DIR}/config/config.h.in ${CMAKE_SOURCE_DIR}/config/config.h @ONLY)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

message(STATUS "build type: " ${CMAKE_BUILD_TYPE})

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PRIVATE 
    tardis-lib
    flatbuf
    zstd::libzstd_static
    )

target_include_directories(${PROJECT_NAME} PUBLIC $ENV{VCPKG_ROOT}/installed/x64-linux/include)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${INSTALL_PATH})
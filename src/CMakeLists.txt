cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "tardis")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME})

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

find_package(spdlog CONFIG REQUIRED)


set(CMAKE_BUILD_TYPE Debug)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(
    ${PROJECT_NAME} PRIVATE 
    tardis-lib
    flatbuf
    )

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/include )

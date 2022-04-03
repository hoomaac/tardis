cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "tardis-lib")

set(TARDIS_LIB_NAME "tardis")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(${PROJECT_NAME})

find_package(spdlog CONFIG REQUIRED)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/uitlity/*.cpp)

message(STATUS "source: " ${SOURCES})

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_SOURCE_DIR}/flatbuf
    )
    
target_link_libraries(${PROJECT_NAME} PUBLIC spdlog::spdlog)

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${TARDIS_LIB_NAME})

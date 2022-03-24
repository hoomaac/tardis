cmake_minimum_required(VERSION 3.22)

set(PROJECT_NAME "flatbuf")

project(${PROJECT_NAME})

#find_package(Protobuf CONFIG REQUIRED)
find_package(Flatbuffers CONFIG REQUIRED)

set(FLATBUF_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libFlatBuf)

if (NOT EXISTS ${FLATBUF_OUTPUT_DIR})
    file(MAKE_DIRECTORY ${FLATBUF_OUTPUT_DIR})
endif()

find_file(FLATBUFFERS_HEADER_FILE flatbuffers/flatbuffers.h)
set(FLATBUF_INCLUDE_DIR "${FLATBUFFERS_HEADER_FILE}" SCOPE_PARENT)

find_program(FLATC flatc)

if (${FLATC}_NOTFOUND)
    message(FATAL_ERROR "Flatc is not installed!")
endif()

file(GLOB FLATBUF_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.fbs")

foreach(flatbuf_file ${FLATBUF_SOURCES})

    file(TO_NATIVE_PATH ${flatbuf_file} flatbuf_native_path)
    execute_process(COMMAND ${FLATC}
        -c --cpp-std c++17 -o ${FLATBUF_OUTPUT_DIR} ${flatbuf_native_path}
        RESULT_VARIABLE rv
    )
    if (${rv})
        message(SEND_ERROR "During generating of ${flatbuf_native_path} an error occured. error=${rv}") 
    endif()

endforeach()

file(GLOB FLAT_HEADERS ${FLATBUF_OUTPUT_DIR}/*.h)

add_library(${PROJECT_NAME} INTERFACE ${FLAT_HEADERS})

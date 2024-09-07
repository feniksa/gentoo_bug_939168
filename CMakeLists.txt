cmake_minimum_required (VERSION 3.18)
project (gentoo_bug_939168 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

option(ASAN "Build with sanitizers" TRUE)

include(cmake/CompileOptions.cmake)

find_package(Protobuf CONFIG REQUIRED)

# dissable boost asio outdated stuff
add_compile_options($<$<COMPILE_LANG_AND_ID:CXX,GNU>:-DBOOST_ASIO_NO_DEPRECATED>)

# ---------------------------------------------------------
# protobuf part
# ---------------------------------------------------------
add_library(serialize OBJECT "${CMAKE_CURRENT_LIST_DIR}/data.proto")
target_link_libraries(serialize PUBLIC protobuf::libprotobuf)
set(PROTO_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(serialize PUBLIC "$<BUILD_INTERFACE:${PROTO_BINARY_DIR}>")

protobuf_generate(
    TARGET serialize
    IMPORT_DIRS "${CMAKE_CURRENT_LIST_DIR}"
    PROTOC_OUT_DIR "${PROTO_BINARY_DIR}")

# ---------------------------------------------------------
# main
# ---------------------------------------------------------
add_executable(main main.cpp)
target_link_libraries(main PRIVATE serialize)

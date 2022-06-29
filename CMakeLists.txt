cmake_minimum_required(VERSION 3.22)
project(QUEUE CXX)

set(CMAKE_CXX_STANDARD 14)

set(sources
        Vector/Vector.h)

add_library(Vector ${sources})
add_executable(QUEUE main.${sources})

target_link_libraries(QUEUE Vector)

cmake_minimum_required(VERSION 3.10)
project(IntToBinaryString)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

include_directories(
        ../include
        ${GTEST_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 14)

add_executable(IntToBinaryString main.cpp)

target_link_libraries(IntToBinaryString ${GTEST_LIBRARIES} Threads::Threads)

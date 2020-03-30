cmake_minimum_required(VERSION 3.10)
project(RemoveDups)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

include_directories(
        ../include
        ${GTEST_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 14)

add_executable(RemoveDups main.cpp)

target_link_libraries(RemoveDups ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()
add_test(RemoveDups "./main.cpp")
cmake_minimum_required(VERSION 3.10)
project(Task2)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)
include_directories(${GTEST_INCLUDE_DIR})

include_directories(
        ../include
        ${GTEST_INCLUDE_DIRS}
)

set(CMAKE_CXX_STANDARD 14)

add_executable(Task2 main.cpp)

target_link_libraries(Task2 ${GTEST_LIBRARIES} Threads::Threads)

enable_testing()
add_test(Task2 "./main.cpp")
find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
        ../include
        ${GTEST_INCLUDE_DIRS}
)

add_executable(
        unit_tests
        main.cpp
        ListNodeTests.cpp
)

target_link_libraries(
        unit_tests
        List
        ${GTEST_LIBRARIES}
        Threads::Threads
)

enable_testing()

add_test(
        NAME
        unit
        COMMAND
        ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/unit_tests
)

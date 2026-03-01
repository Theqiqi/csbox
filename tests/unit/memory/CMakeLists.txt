cmake_minimum_required(VERSION 3.21)

find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES
    AddressOffsetsTest.cpp
)

add_executable(csbox_memory_test ${TEST_SOURCES})

target_include_directories(csbox_memory_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/memory
)

target_link_libraries(csbox_memory_test PRIVATE
    GTest::gtest
    GTest::gtest_main
    csbox_memory
)

include(GoogleTest)
gtest_discover_tests(csbox_memory_test)

cmake_minimum_required(VERSION 3.21)

find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES
    Vector3Test.cpp
    Matrix4x4Test.cpp
    WorldToScreenTest.cpp
)

add_executable(csbox_math_test ${TEST_SOURCES})

target_include_directories(csbox_math_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/math
)

target_link_libraries(csbox_math_test PRIVATE
    GTest::gtest
    GTest::gtest_main
    csbox_math
)

include(GoogleTest)
gtest_discover_tests(csbox_math_test)

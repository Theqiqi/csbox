cmake_minimum_required(VERSION 3.21)

find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES
    ArgumentParserTest.cpp
)

add_executable(csbox_common_test ${TEST_SOURCES})

target_include_directories(csbox_common_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/common
)

target_link_libraries(csbox_common_test PRIVATE
    GTest::gtest
    GTest::gtest_main
    csbox_common
)

include(GoogleTest)
gtest_discover_tests(csbox_common_test)
if(MSVC)
    target_compile_options(csbox_common_test PRIVATE /EHsc)
endif()
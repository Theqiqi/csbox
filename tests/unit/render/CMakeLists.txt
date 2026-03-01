cmake_minimum_required(VERSION 3.21)

find_package(GTest CONFIG REQUIRED)

set(TEST_SOURCES
    RendererTest.cpp
)

add_executable(csbox_render_test ${TEST_SOURCES})

target_include_directories(csbox_render_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/src/render
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_SOURCE_DIR}/src/math
)

target_link_libraries(csbox_render_test PRIVATE
    GTest::gtest
    GTest::gtest_main
    csbox_render
    csbox_game
    csbox_math
)

include(GoogleTest)
gtest_discover_tests(csbox_render_test)

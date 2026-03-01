cmake_minimum_required(VERSION 3.21)
project(csbox_game)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/math
)
target_link_libraries(${PROJECT_NAME} INTERFACE csbox_math)

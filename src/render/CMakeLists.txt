cmake_minimum_required(VERSION 3.21)
project(csbox_render LANGUAGES CXX)

set(SOURCES 
    Renderer.h
    Renderer.cpp
    OverlayWindow.h
    OverlayWindow.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/game
    ${CMAKE_SOURCE_DIR}/src/math
    ${CMAKE_SOURCE_DIR}/src/common
)

find_package(raylib CONFIG REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC 
    raylib
    csbox_game
    csbox_math
    csbox_common
)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()


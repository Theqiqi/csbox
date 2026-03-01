cmake_minimum_required(VERSION 3.21)

set(LIB_SOURCES
    GameEngine.cpp
)

add_library(csbox_engine STATIC ${LIB_SOURCES})

target_include_directories(csbox_engine PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(csbox_engine PUBLIC
    csbox_memory
    csbox_render
    csbox_windowutils
    csbox_game
    csbox_math
    csbox_common
    raylib
)

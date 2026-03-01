cmake_minimum_required(VERSION 3.29)
project(csbox VERSION 1.0.0 LANGUAGES CXX C)

if(MSVC)
    add_compile_options(/utf-8)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DCSBOX_DEBUG)
endif()

# 避免 raylib 与 Windows API 头文件冲突
add_definitions(-DNOMINMAX)

find_package(raylib CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_subdirectory(src/common)
add_subdirectory(src/math)
add_subdirectory(src/game)
add_subdirectory(src/memory)
add_subdirectory(src/WindowUtils)
add_subdirectory(src/render)
add_subdirectory(src/engine)

# 主程序
set(SOURCES src/main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    raylib
    glfw
    opengl32 gdi32 winmm shell32 user32
    csbox_engine csbox_render csbox_game csbox_math csbox_memory csbox_windowutils csbox_common
)

if(MSVC)
    target_compile_options(csbox PRIVATE /utf-8)
endif()

# Keep console for debugging
if(WIN32)
     target_link_options(${PROJECT_NAME} PRIVATE "/SUBSYSTEM:WINDOWS" "/ENTRY:mainCRTStartup")
endif()

# 测试
enable_testing()
add_subdirectory(tests/unit)

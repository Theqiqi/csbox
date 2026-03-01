cmake_minimum_required(VERSION 3.21)
project(csbox_windowutils LANGUAGES CXX)

set(SOURCES 
    WindowUtils.h
    WindowUtils.cpp
)
add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src/common
)

target_link_libraries(${PROJECT_NAME} PRIVATE csbox_common)

if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /utf-8)
endif()

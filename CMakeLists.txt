cmake_minimum_required(VERSION 3.16)

project(weather VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Find Raylib
find_package(raylib REQUIRED)

# Includes
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/json/include
)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link with raylib
target_link_libraries(${PROJECT_NAME} raylib)
message(STATUS "Include dir: ${CMAKE_SOURCE_DIR}/include")
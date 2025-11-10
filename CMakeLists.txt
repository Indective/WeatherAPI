cmake_minimum_required(VERSION 3.16)

# Project name and version
project(weather VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/external/json/include
)
# Add the executable
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m pthread dl rt X11)
endif()
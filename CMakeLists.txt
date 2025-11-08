cmake_minimum_required(VERSION 3.16)

# Project name and version
project(weather VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
add_subdirectory(external/nlohmann) 

# Add the executable
file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(weather PRIVATE nlohmann_json::nlohmann_json)

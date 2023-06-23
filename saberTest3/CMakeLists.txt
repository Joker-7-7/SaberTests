cmake_minimum_required(VERSION 3.5)

project(saberTest3 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_EXE main.cpp List.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_EXE})

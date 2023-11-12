cmake_minimum_required(VERSION 3.20)

project(taskmaster VERSION 0.1)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)

add_executable(${PROJECT_NAME} main.c tree.c runner.c)

target_include_directories(${PROJECT_NAME} PUBLIC ./refactor)

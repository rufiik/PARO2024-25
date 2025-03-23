cmake_minimum_required(VERSION 3.10.0)
project(PARO-workshop VERSION 1.0)

enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-Wall -Wextra -Wpedantic)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(gtest)
add_subdirectory(exercise1)
add_subdirectory(exercise2)
add_subdirectory(application)



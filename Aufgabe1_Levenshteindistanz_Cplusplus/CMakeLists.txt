# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(termcalc)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add executable target with source files
add_executable(${PROJECT_NAME} termcalc.cpp)

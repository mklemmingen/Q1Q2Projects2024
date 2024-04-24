# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(card_restorer)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)

# Add executable target with source files
add_executable(${PROJECT_NAME} card_restorer.cpp strtool.cpp distcalc.cpp)
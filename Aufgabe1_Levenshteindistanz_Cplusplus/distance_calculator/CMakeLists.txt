cmake_minimum_required(VERSION 3.10)

project(termcalc)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} termcalc.cpp strtool.cpp distcalc.cpp)
cmake_minimum_required(VERSION 3.10)

project(card_restorer)

set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} card_restorer.cpp 
                                distance_calculator/strtool.cpp 
                                distance_calculator/distcalc.cpp)
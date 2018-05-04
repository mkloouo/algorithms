cmake_minimum_required(VERSION 3.10)
project(algorithms)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME} main.cpp HuffmanAlgorithm.cpp HuffmanAlgorithm.h)
target_link_libraries(${PROJECT_NAME} pthread)
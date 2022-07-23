cmake_minimum_required(VERSION 3.17)
project(RTree)

set(CMAKE_CXX_STANDARD 20)

add_executable(AVL main.cpp RTree.cpp Node.cpp clase.h)
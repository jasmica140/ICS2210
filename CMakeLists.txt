cmake_minimum_required(VERSION 3.24)
project(ICS2210)

set(CMAKE_CXX_STANDARD 17)

add_executable(ICS2210 knuthShuffe.cpp main.cpp skipList.cpp knuthShuffe.h AVLTree.cpp AVLTree.h skipList.h node.cpp node.h)

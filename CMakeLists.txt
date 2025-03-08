cmake_minimum_required(VERSION 3.30)
project(Common_Occurrence_With_Dynamic_Stacks)

set(CMAKE_CXX_STANDARD 20)

add_executable(Common_Occurrence_With_Dynamic_Stacks main.cpp
        DynStringStack.cpp
        DynStringStack.h)

cmake_minimum_required(VERSION 3.17)
project(Flight_Scheduling)

set(CMAKE_CXX_STANDARD 20)

add_executable(Flight_Scheduling main.cpp DataLoader.h ALGraph.cpp ALGraph.h DataLoader.cpp)
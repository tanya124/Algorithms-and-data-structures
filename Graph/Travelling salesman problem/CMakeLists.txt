cmake_minimum_required(VERSION 3.13)
project(untitled2)

set(CMAKE_CXX_STANDARD 11)

add_executable(untitled2 scource.cpp src/MST.cpp include/MST.h src/DSU.cpp include/DSU.h src/Graph.cpp include/Graph.h src/TSP.cpp include/TSP.h src/Generator.cpp include/Generator.h src/TSP_2.cpp include/TSP_2.h src/test.cpp include/test.h)
cmake_minimum_required(VERSION 3.22)
project(p3)

set(CMAKE_CXX_STANDARD 14)

add_executable(p3 p3.cpp PatientPriorityQueue.h Patient.h)

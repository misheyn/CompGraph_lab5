cmake_minimum_required(VERSION 3.20)
project(CompGraph_lab5)

set(CMAKE_CXX_STANDARD 20)

add_executable(CompGraph_lab5 main.cpp FillPolygon.cpp FillPolygon.h)

target_link_libraries(CompGraph_lab5 -lOpenGL32 -lfreeGLUT -lGLU32)
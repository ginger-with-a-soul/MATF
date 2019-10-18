cmake_minimum_required(VERSION 3.15)
project(cas2)

set(CMAKE_CXX_STANDARD 14)

link_libraries(GL)
link_libraries(GLU)
link_libraries(glut)

add_executable(cas2 07cube_3D.cpp)
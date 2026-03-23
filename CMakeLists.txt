cmake_minimum_required(VERSION 3.15)
project(RubiksCube)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE OpenGL::GL GLUT::GLUT)

if(APPLE)
    target_compile_options(app PRIVATE -Wno-deprecated-declarations)
    target_compile_definitions(app PRIVATE GL_SILENCE_DEPRECATION)
endif()
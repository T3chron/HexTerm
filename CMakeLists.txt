cmake_minimum_required(VERSION 4.0)
project(HexTerm)

set(CMAKE_CXX_STANDARD 26)
add_compile_options(-Wno-deprecated-declarations)

add_executable(HexTerm main.cpp
        HexCore/HexTermCore.cpp)
target_link_libraries(HexTerm PRIVATE winmm)
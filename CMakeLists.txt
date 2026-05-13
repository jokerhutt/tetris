cmake_minimum_required(VERSION 3.10)

project(tetris)

set(CMAKE_CXX_STANDARD 20)

include_directories(/opt/homebrew/include)
link_directories(/opt/homebrew/lib)

add_executable(tetris 
    src/main.cpp 
    src/position.cpp
    src/grid.cpp
    src/colors.cpp
    src/block.h
)

target_link_libraries(tetris raylib)


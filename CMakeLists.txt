cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
# add the executable
add_executable(Tetris.out main.cpp block.cpp board.cpp shape.cpp)
target_link_libraries(Tetris.out ncurses)

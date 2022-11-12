cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
# add the executable
add_executable(Tetris.out main.cpp block.cpp board.cpp shape.cpp timer.cpp ui.cpp screenHandler.cpp square.cpp)

#File for profiler
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
add_compile_options(-pg -no-pie -fno-builtin)
add_executable(TetrisProfiler.out main.cpp block.cpp board.cpp shape.cpp timer.cpp ui.cpp screenHandler.cpp square.cpp)
target_link_libraries(Tetris.out ncurses)
target_link_libraries(TetrisProfiler.out ncurses)

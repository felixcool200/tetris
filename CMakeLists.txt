cmake_minimum_required(VERSION 3.10)

# set the project name
project(Tetris)

set(CMAKE_CXX_STANDARD 17)
# add the executable

include_directories(include/)
add_executable(Tetris.out src/main.cpp src/tetromino.cpp src/game.cpp src/timer.cpp src/ui.cpp src/screenHandler.cpp src/square.cpp)

#File for profiler
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -pg")
add_compile_options(-pg -no-pie -fno-builtin)

add_executable(TetrisProfiler.out src/main.cpp src/tetromino.cpp src/game.cpp src/timer.cpp src/ui.cpp src/screenHandler.cpp src/square.cpp)
target_link_libraries(Tetris.out ncurses)
target_link_libraries(TetrisProfiler.out ncurses)

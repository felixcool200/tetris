cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Tetris)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
set(INCLUDE_DIR "include/")
set(SOURCE_FILES src/main.cpp src/tetromino.cpp src/game.cpp src/timer.cpp src/ui.cpp src/ncursesScreen.cpp src/square.cpp)

# Create main executable
add_executable(Tetris.out ${SOURCE_FILES})
target_include_directories(Tetris.out PRIVATE ${INCLUDE_DIR})
target_link_libraries(Tetris.out ncurses)

# Create profiler executable
add_executable(TetrisProfiler.out ${SOURCE_FILES})
target_include_directories(TetrisProfiler.out PRIVATE ${INCLUDE_DIR})
target_link_libraries(TetrisProfiler.out ncurses)

# Profiling options for the profiler build
target_compile_options(TetrisProfiler.out PRIVATE -pg -no-pie -fno-builtin)
target_link_options(TetrisProfiler.out PRIVATE -pg)

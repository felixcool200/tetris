cmake_minimum_required(VERSION 3.14)

project(Tetris)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the build type" FORCE)
endif()

# Includes and sources
set(INCLUDE_DIR "include/")
set(SOURCE_FILES
    src/main.cpp
    src/tetromino.cpp
    src/game.cpp
    src/timer.cpp
    src/ui.cpp
    src/square.cpp
)

# Option for selecting the screen type (default to raylib)
option(SCREEN_TYPE "Select screen renderer (ncurses, or raylib)" "raylib")

# Add screen implementation based on selected SCREEN_TYPE
if(SCREEN_TYPE STREQUAL "ncurses")
    message(STATUS "Using ncurses as the screen renderer")
    list(APPEND SOURCE_FILES src/ncursesScreen.cpp)
    find_package(Curses REQUIRED)
    set(SCREEN_LIBS ncurses)
    add_definitions(-DSCREEN_NCURSES)

elseif(SCREEN_TYPE STREQUAL "raylib")
    message(STATUS "Using raylib as the screen renderer")
    list(APPEND SOURCE_FILES src/raylibScreen.cpp)
    
    # Raylib setup (fetch raylib only if needed)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )
    FetchContent_MakeAvailable(raylib)
    set(SCREEN_LIBS raylib)
    add_definitions(-DSCREEN_RAYLIB)

else()
    message(FATAL_ERROR "Unknown SCREEN_TYPE '${SCREEN_TYPE}', please choose 'ncurses', or 'raylib'")
endif()

# Main executable
add_executable(Tetris.out ${SOURCE_FILES})
target_include_directories(Tetris.out PRIVATE ${INCLUDE_DIR})

# Link appropriate libraries
target_link_libraries(Tetris.out ${SCREEN_LIBS})

# Compiler warnings (non-profiler build)
target_compile_options(Tetris.out PRIVATE
    -Werror -Wpedantic -Wuninitialized -Wredundant-decls
    -Wfloat-equal -Wall -Wextra -Wcast-qual -Wconversion
    -Wshadow -Wunused-parameter -Wwrite-strings -Wno-variadic-macros
)

# Optionally, you can add a profiling build as before
#add_executable(TetrisProfiler.out ${SOURCE_FILES})
#target_include_directories(TetrisProfiler.out PRIVATE ${INCLUDE_DIR})
#target_link_libraries(TetrisProfiler.out ${SCREEN_LIBS})
#target_compile_options(TetrisProfiler.out PRIVATE -pg -no-pie -fno-builtin)
#target_link_options(TetrisProfiler.out PRIVATE -pg)

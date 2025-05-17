cmake_minimum_required(VERSION 3.14)

project(Tetris)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export command to allow use with clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

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
    set(SCREEN_DEFINE SCREEN_NCURSES)

elseif(SCREEN_TYPE STREQUAL "raylib")
    message(STATUS "Using raylib as the screen renderer")
    list(APPEND SOURCE_FILES src/raylibScreen.cpp)

    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
    )
    FetchContent_MakeAvailable(raylib)
    set(SCREEN_LIBS raylib)
    set(SCREEN_DEFINE SCREEN_RAYLIB)

    # Suppress warnings for Raylib
    target_compile_options(raylib PRIVATE 
        -Wno-unused-result    # Suppress unused return value warnings
        -Wno-stringop-overflow # Suppress string overflow warnings
    )
else()
    message(FATAL_ERROR "Unknown SCREEN_TYPE '${SCREEN_TYPE}', please choose 'ncurses', or 'raylib'")
endif()


# Create library
add_library(tetris_core ${SOURCE_FILES})
target_include_directories(tetris_core PUBLIC ${INCLUDE_DIR})
target_compile_definitions(tetris_core PUBLIC ${SCREEN_DEFINE})
target_link_libraries(tetris_core PUBLIC ${SCREEN_LIBS})


# Main executable
add_executable(Tetris.out src/main.cpp)
target_link_libraries(Tetris.out PRIVATE tetris_core)

# Compiler warnings (non-profiler build)
target_compile_options(Tetris.out PRIVATE
    -Werror
    -Wpedantic
    -Wall
    -Wextra
    -Wuninitialized
    -Wshadow
    -Wredundant-decls
    -Wfloat-equal
    -Wcast-qual
    -Wconversion
    -Wunused-parameter
    -Wunused-variable
    -Wwrite-strings
    -Wno-variadic-macros
    -Wnull-dereference
    -Wdeprecated
    -Wsign-compare
    -Wmissing-declarations
    -Wuseless-cast
    -Wfloat-conversion
    -Wformat=2
    -fno-common
    -fanalyzer
    -Wno-analyzer-use-of-uninitialized-value
    -O3
    -fno-omit-frame-pointer
)

target_link_options(Tetris.out PRIVATE
    -Wl,-z,now
    -Wl,-z,relro
)

# Add tests directory
add_subdirectory(tests)
enable_testing()
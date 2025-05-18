message(STATUS "Fetching Catch2")
Include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 # or a later release
)

FetchContent_MakeAvailable(Catch2)

# These tests can use the Catch2-provided main
add_executable(unittests
    # Tests
    test_game.cpp
    test_square.cpp
    test_tetramino.cpp
)
target_link_libraries(unittests PRIVATE Catch2::Catch2WithMain)

# Optionally link to core game logic if needed
target_link_libraries(unittests PRIVATE tetris_core)
target_include_directories(unittests PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(CTest)
include(Catch)

catch_discover_tests(unittests)
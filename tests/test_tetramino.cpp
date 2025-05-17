#include <catch2/catch_test_macros.hpp>
#include <common.hpp>
#include <mockScreen.hpp>
#include <tetromino.hpp>

#include "mockScreen.hpp"

TEST_CASE("Tetromino starts at expected initial position") {
    Tetromino t;

    REQUIRE(t.getX() == (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2);
    REQUIRE(t.getY() == -1);
    REQUIRE_FALSE(t.hasBeenHeld());
}

TEST_CASE("Tetromino tick increases Y position") {
    Tetromino t;
    int initialY = t.getY();

    t.tick();

    REQUIRE(t.getY() == initialY + 1);
}

TEST_CASE("Tetromino can be held") {
    Tetromino t;
    REQUIRE_FALSE(t.hasBeenHeld());

    t.hold();

    REQUIRE(t.hasBeenHeld());
}
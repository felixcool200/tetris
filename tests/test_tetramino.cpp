#include <catch2/catch_test_macros.hpp>

#include "common.hpp"
#include "mockScreen.hpp"
#include "tetromino.hpp"

TEST_CASE("Tetromino starts at expected initial position", "[tetromino]") {
    Tetromino t;
    CHECK(t.getX() == (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2);
    CHECK(t.getY() == -1);
    CHECK_FALSE(t.hasBeenHeld());
}

TEST_CASE("Tetromino tick once increases Y position", "[tetromino]") {
    Tetromino t;

    int initialY = t.getY();

    t.tick();

    CHECK(t.getY() == initialY + 1);
}

TEST_CASE("Tetromino ticks increases Y position", "[tetromino]") {
    Tetromino t;

    int initialY = t.getY();

    for (int i = 0; i < 5; ++i) {
        t.tick();
    }

    CHECK(t.getY() == initialY + 5);
}

TEST_CASE("Tetromino can be moved", "[tetromino]") {
    Tetromino t;

    CHECK(t.getX() == (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2);
    CHECK(t.getY() == -1);

    for (int i = 0; i < 5; ++i) {
        t.move(tetris::Direction::DOWN);
        t.move(tetris::Direction::RIGHT);
    }

    // Has Tetromino moved
    CHECK(t.getX() == 8);
    CHECK(t.getY() == 4);

    for (int i = 0; i < 2; ++i) {
        t.move(tetris::Direction::UP);
        t.move(tetris::Direction::LEFT);
    }

    // Has Tetromino moved
    CHECK(t.getX() == 6);
    CHECK(t.getY() == 2);
}

TEST_CASE("Tetromino can be held", "[tetromino]") {
    Tetromino t;

    CHECK_FALSE(t.hasBeenHeld());

    for (int i = 0; i < 5; ++i) {
        t.move(tetris::Direction::DOWN);
        t.move(tetris::Direction::RIGHT);
    }

    t.hold();

    // Is position reset?
    CHECK(t.getX() == (tetris::BOARD_WIDTH - tetris::SHAPESIZE) / 2);
    CHECK(t.getY() == -1);
    CHECK(t.hasBeenHeld());
}

/*
TODO: Remove random from Tetromino constructor to make it testable
TODO: Left to test is:
    bool isFilledAt(int x, int y) const;
    void rotateRight()
    tetris::Color getColor() const tetris::Color getPreviewColor()
    char getShape() const;
*/
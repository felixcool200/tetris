#include <cassert>
#include <catch2/catch_test_macros.hpp>

#include "gameHelper.hpp"
#include "tetrominoHelper.hpp"

// Helper function to clear a given number of lines by simulating O-tetromino drops.
// Each iteration places 5 O-blocks (2x2) side by side to fill and clear lines.
void clearLines(GameTestHelper& gameTest, int lines = 2) {
    // The number of lines must be even because each O-tetromino (2x2) clears two lines per
    // placement.
    assert(lines % 2 == 0);
    gameTest.setCurrentTetromino(Tetromino(0));
    // Simulate clearing 'lines' lines (must be even, as each O-block clears 2 lines)
    for (int i = 0; i < lines / 2; ++i) {
        // Place 5 O-blocks from left to right to fill the bottom two rows
        gameTest.setNextTetromino(Tetromino(0));
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::DROP);

        gameTest.setNextTetromino(Tetromino(0));
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::LEFT);
        gameTest.getGame().update(tetris::Control::DROP);

        gameTest.setNextTetromino(Tetromino(0));
        gameTest.getGame().update(tetris::Control::DROP);

        gameTest.setNextTetromino(Tetromino(0));
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::DROP);

        gameTest.setNextTetromino(Tetromino(0));
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::RIGHT);
        gameTest.getGame().update(tetris::Control::DROP);
    }
}

// Test: The default state of the game is as expected (initial speed, not game over, no tetromino
// placed)
TEST_CASE("Game default state") {
    GameTestHelper gameTest(Tetromino(0));
    CHECK(gameTest.getGame().getFramesPerTick() == 97);
    CHECK(gameTest.getGame().isGameOver() == false);
    CHECK(gameTest.getGame().wasTetrominoJustPlaced() == false);
}

// Test: The result string is correct before and after dropping tetrominos (score/lines update)
TEST_CASE("Game test result string") {
    GameTestHelper gameTest(Tetromino(0));
    const std::string emtpyResult =
        std::string("Game over \nResult\n\tLines cleared: 0\n\tScore: 0");
    CHECK(gameTest.getGame().getResult() == emtpyResult);

    // Earn points, drop three tetrominos
    gameTest.getGame().update(tetris::Control::DROP);
    gameTest.getGame().update(tetris::Control::DROP);
    gameTest.getGame().update(tetris::Control::DROP);

    CHECK(gameTest.getGame().getResult() != emtpyResult);
}

// Test: The static border checker correctly identifies valid and invalid board coordinates
TEST_CASE("Game test border checker") {
    GameTestHelper gameTest(Tetromino(0));
    const std::vector<std::pair<std::pair<int, int>, bool>> test_cases = {
        {{0, 0}, true},
        {{tetris::BOARD_WIDTH - 1, tetris::BOARD_HEIGHT - 1}, true},
        {{5, 10}, true},
        {{8, 15}, true},
        {{-1, 0}, false},
        {{0, -1}, false},
        {{tetris::BOARD_WIDTH, 0}, false},
        {{0, tetris::BOARD_HEIGHT}, false},
        {{tetris::BOARD_WIDTH, tetris::BOARD_HEIGHT}, false},
    };

    for (const auto& [coords, expected] : test_cases) {
        CHECK(Game::s_isOnBoard(coords.first, coords.second) == expected);
    }
}

// Test: Placing a single O-block at the leftmost position fills the correct cells on the board
TEST_CASE("Game tick can place a block to board") {
    GameTestHelper gameTest(Tetromino(0));

    // Move the tetromino all the way to the left
    for (int i = 0; i < tetris::BOARD_WIDTH / 2 - 1; ++i) {
        gameTest.getGame().update(tetris::Control::LEFT);
    }

    // Drop the tetromino to the bottom of the board
    for (int i = 0; i < tetris::BOARD_HEIGHT - 1; ++i) {
        gameTest.getGame().tick();
    }

    // Prepare test cases for the O block (bottom left 2x2 should be occupied)
    const std::vector<std::pair<std::pair<int, int>, bool>> test_cases = {
        // Blocks that should be filled
        {{0, tetris::BOARD_HEIGHT - 1}, true},
        {{0, tetris::BOARD_HEIGHT - 2}, true},

        {{1, tetris::BOARD_HEIGHT - 1}, true},
        {{1, tetris::BOARD_HEIGHT - 2}, true},

        // Off by one y (should not be filled)
        {{0, tetris::BOARD_HEIGHT - 3}, false},
        {{1, tetris::BOARD_HEIGHT - 3}, false},
        {{2, tetris::BOARD_HEIGHT - 3}, false},

        // Off by one x (should not be filled)
        {{2, tetris::BOARD_HEIGHT - 1}, false},
        {{2, tetris::BOARD_HEIGHT - 2}, false},
    };

    // Get the current board state after placing the block
    const auto currentBoard = gameTest.getBoard();
    // Check that the expected cells are filled or empty as specified
    for (const auto& [coords, expected] : test_cases) {
        CHECK(currentBoard[coords.first][coords.second].isPlaced() == expected);
    }
}

// Test: Placing two O-blocks on top of each other at the leftmost position fills the correct cells
TEST_CASE("Game tick can place two blocks on top of each other") {
    GameTestHelper gameTest(Tetromino(0));

    gameTest.setNextTetromino(Tetromino(0));

    for (int j = 0; j < 2; ++j) {
        // Move block all the way to the left
        for (int i = 0; i < tetris::BOARD_WIDTH / 2 - 1; ++i) {
            gameTest.getGame().update(tetris::Control::LEFT);
        }

        // Drop the block to the bottom
        for (int i = 0; i < tetris::BOARD_HEIGHT - 1; ++i) {
            gameTest.getGame().tick();
        }
    }

    // After dropping two O blocks on the far left, the bottom 4 cells (2x2) and the 2 cells above

    const std::vector<std::pair<std::pair<int, int>, bool>> test_cases = {
        // Bottom O block
        {{0, tetris::BOARD_HEIGHT - 1}, true},
        {{0, tetris::BOARD_HEIGHT - 2}, true},
        {{1, tetris::BOARD_HEIGHT - 1}, true},
        {{1, tetris::BOARD_HEIGHT - 2}, true},

        // Top O block (directly above)
        {{0, tetris::BOARD_HEIGHT - 3}, true},
        {{0, tetris::BOARD_HEIGHT - 4}, true},
        {{1, tetris::BOARD_HEIGHT - 3}, true},
        {{1, tetris::BOARD_HEIGHT - 4}, true},

        // Off by one y (should not be filled)
        {{0, tetris::BOARD_HEIGHT - 5}, false},
        {{1, tetris::BOARD_HEIGHT - 5}, false},
        {{2, tetris::BOARD_HEIGHT - 5}, false},

        // Off by one x (should not be filled)
        {{2, tetris::BOARD_HEIGHT - 1}, false},
        {{2, tetris::BOARD_HEIGHT - 2}, false},
        {{2, tetris::BOARD_HEIGHT - 3}, false},
        {{2, tetris::BOARD_HEIGHT - 4}, false},
    };

    // Get the current board state after placing the blocks
    const auto currentBoard = gameTest.getBoard();
    // Check that the expected cells are filled or empty as specified
    for (const auto& [coords, expected] : test_cases) {
        CHECK(currentBoard[coords.first][coords.second].isPlaced() == expected);
    }
}

// Test: checkForObstruction detects collisions with boundaries and placed blocks
TEST_CASE("Game::checkForObstruction detects collisions and boundaries", "[game][obstruction]") {
    GameTestHelper gameTest(Tetromino(0));
    Tetromino t = Tetromino(0);

    // Place at a valid position
    t.move(tetris::Direction::DOWN);
    CHECK_FALSE(gameTest.checkForObstruction(t));

    // Move out of bounds (left)
    for (int i = 0; i < 10; ++i) t.move(tetris::Direction::LEFT);
    CHECK(gameTest.checkForObstruction(t));

    // Place a block and check collision
    Tetromino t2 = Tetromino(0);
    t2.move(tetris::Direction::DOWN);
    gameTest.addTetrominoToBoard(t2);
    CHECK(gameTest.checkForObstruction(t2));
}

// Test: createPreview sets the preview tetromino to the lowest unobstructed position
TEST_CASE("Game::createPreview sets preview to lowest unobstructed position", "[game][preview]") {
    GameTestHelper gameTest(Tetromino(0));
    gameTest.createPreview();
    auto preview = gameTest.getTetrominoPreview();
    auto original = gameTest.getTetromino();

    // Preview should be at the same X, but as low as possible
    CHECK(preview.getX() == original.getX());
    CHECK(preview.getY() > original.getY());
    // Should be obstructed if moved further down
    Tetromino test = preview;
    test.move(tetris::Direction::DOWN);
    CHECK(gameTest.checkForObstruction(test));
}

// Test: dropTetromino moves the current tetromino to the bottom and places it
TEST_CASE("Game::dropTetromino moves tetromino to bottom and places it", "[game][drop]") {
    GameTestHelper gameTest(Tetromino(0));
    auto originalX = gameTest.getTetromino().getX() + 1;
    gameTest.dropTetromino();
    // After drop, the tetromino should be placed at the bottom
    const auto& board = gameTest.getBoard();
    CHECK(board[originalX][tetris::BOARD_HEIGHT - 1].isPlaced());
}

// Test: placeTetromino places the current tetromino on the board at its current position
TEST_CASE("Game::placeTetromino places current tetromino on board", "[game][place]") {
    GameTestHelper gameTest(Tetromino(0));
    auto t = gameTest.getTetromino();
    t.move(tetris::Direction::DOWN);
    gameTest.setCurrentTetromino(t);
    gameTest.placeTetromino();
    const auto& board = gameTest.getBoard();
    CHECK(board[t.getX() + 1][t.getY() + 1].isPlaced());
}

// Test: addTetrominoToBoard places all filled squares of a tetromino onto the board
TEST_CASE("Game::addTetrominoToBoard places all filled squares", "[game][addToBoard]") {
    GameTestHelper gameTest(Tetromino(0));
    Tetromino t(0);
    t.move(tetris::Direction::DOWN);
    gameTest.addTetrominoToBoard(t);
    const auto& board = gameTest.getBoard();
    // Check all filled cells of the tetromino are placed on the board
    for (size_t dx = 0; dx < tetris::SHAPESIZE; ++dx) {
        for (size_t dy = 0; dy < tetris::SHAPESIZE; ++dy) {
            if (t.isFilledAt(dx, dy)) {
                CHECK(board[t.getX() + dx][t.getY() + dy].isPlaced());
            }
        }
    }
}

// Test: removeCompleteRows removes filled rows and updates score/lines
TEST_CASE("Game::removeCompleteRows removes filled rows and updates score/lines",
          "[game][removeRows]") {
    GameTestHelper gameTest(Tetromino(0));
    // Fill bottom row
    for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
        gameTest.getBoard()[x][tetris::BOARD_HEIGHT - 1].place(tetris::Color::TETROMINO_RED);
    }
    gameTest.removeCompleteRows();
    // After removal, bottom row should be empty
    for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
        CHECK_FALSE(gameTest.getBoard()[x][tetris::BOARD_HEIGHT - 1].isPlaced());
    }
    CHECK(gameTest.getGame().getResult().find("Lines cleared: 1") != std::string::npos);
}

// Test: createNewTetromino sets the current tetromino to the next tetromino
TEST_CASE("Game::createNewTetromino sets current tetromino to next", "[game][newTetromino]") {
    GameTestHelper gameTest(Tetromino(0));
    Tetromino next(1);
    gameTest.setNextTetromino(next);
    gameTest.createNewTetromino();
    CHECK(gameTest.getTetromino().getShape() == next.getShape());
}

// Test: removeRow shifts all rows above the removed row down by one
TEST_CASE("Game::removeRow shifts rows down", "[game][removeRow]") {
    GameTestHelper gameTest(Tetromino(0));
    // Fill two rows
    for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
        gameTest.getBoard()[x][10].place(tetris::Color::TETROMINO_RED);
        gameTest.getBoard()[x][9].place(tetris::Color::TETROMINO_BLUE);
    }
    gameTest.removeRow(10);
    // Row 10 should now be blue (was row 9)
    for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
        CHECK(gameTest.getBoard()[x][10].getColor() == tetris::Color::TETROMINO_BLUE);
    }
}

// Test: updateLevel increases the level after clearing enough lines
TEST_CASE("Game::updateLevel increases level after clearing lines", "[game][level]") {
    GameTestHelper gameTest(Tetromino(0));
    clearLines(gameTest, 10);
    gameTest.updateLevel();
    CHECK(gameTest.getGame().getResult().find("Lines cleared: 10") != std::string::npos);
    CHECK(gameTest.getGame().getFramesPerTick() < 97);  // Should be faster
}

// Test: updateSpeed sets frames per tick according to the current level (speed increases)
TEST_CASE("Game::updateSpeed sets frames per tick according to level", "[game][speed]") {
    GameTestHelper gameTest(Tetromino(0));
    size_t prevFrames = gameTest.getGame().getFramesPerTick();
    // Simulate level up
    clearLines(gameTest, 50);
    gameTest.updateSpeed();
    CHECK(gameTest.getGame().getFramesPerTick() < prevFrames);
}
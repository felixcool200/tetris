#include <cassert>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

#include "gameHelper.hpp"
#include "tetrominoHelper.hpp"

GameTestHelper stableGame(const size_t shapeIndex = 0) {
    assert(shapeIndex <= TetrominoTestHelper::getTotalTetrominos());
    GameTestHelper gameTest;

    TetrominoTestHelper tetrominoHelp;

    tetrominoHelp.setShape(shapeIndex);
    gameTest.setCurrentTetromino(tetrominoHelp.getTetromino());
    return gameTest;
};

void setNextTetromino(GameTestHelper& gameTest, const size_t shapeIndex = 0) {
    assert(shapeIndex <= TetrominoTestHelper::getTotalTetrominos());

    TetrominoTestHelper tetrominoHelp;

    tetrominoHelp.setShape(shapeIndex);
    gameTest.setNextTetromino(tetrominoHelp.getTetromino());
};

void setCurrentTetromino(GameTestHelper& gameTest, const size_t shapeIndex = 0) {
    assert(shapeIndex <= TetrominoTestHelper::getTotalTetrominos());

    TetrominoTestHelper tetrominoHelp;

    tetrominoHelp.setShape(shapeIndex);
    gameTest.setCurrentTetromino(tetrominoHelp.getTetromino());
};

TEST_CASE("Game default state") {
    GameTestHelper gameTest = stableGame();
    CHECK(gameTest.getGame().getFramesPerTick() == 97);
    CHECK(gameTest.getGame().isGameOver() == false);
    CHECK(gameTest.getGame().wasTetrominoJustPlaced() == false);
}

TEST_CASE("Game test result string") {
    GameTestHelper gameTest = stableGame();
    const std::string emtpyResult =
        std::string("Game over \nResult\n\tLines cleared: 0\n\tScore: 0");
    CHECK(gameTest.getGame().getResult() == emtpyResult);

    // Earn points, drop three tetrominos
    gameTest.getGame().update(tetris::Control::DROP);
    gameTest.getGame().update(tetris::Control::DROP);
    gameTest.getGame().update(tetris::Control::DROP);

    CHECK(gameTest.getGame().getResult() != emtpyResult);
}

TEST_CASE("Game test border checker") {
    GameTestHelper gameTest = stableGame();
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

TEST_CASE("Game tick can place a block to board") {
    // Create a stable game state with a known tetromino (O block by default)
    GameTestHelper gameTest = stableGame();

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

TEST_CASE("Game tick can place two blocks on top of each other") {
    // Create a stable game state with a known tetromino (O block by default)
    GameTestHelper gameTest = stableGame();

    setNextTetromino(gameTest);  // Set next tetromino to default (O block)

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
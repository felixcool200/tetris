#include <cassert>
#include <game.hpp>
#include <iostream>

Game::Game() {
    updateSpeed();
    createPreview();
}

void Game::tick() {
    // The end of a tick is where we check if we are done, this gives the player
    // a chance to recover even when the tetromino is touching other blocks
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true;
        return;
    }

    // See if we can move the tetromino down one if not place it.
    if (checkForObstruction(Tetromino::testTick(m_tetromino))) {
        placeTetromino();
    } else {
        m_tetromino.tick();
    }
}

void Game::addTetrominoToBoard(const Tetromino& bl) {
    const int x = bl.getX();
    const int y = bl.getY();
    for (int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
        for (int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
            if (bl.isFilledAt(dx, dy) && s_isOnBoard(x + dx, y + dy)) {
                m_board[x + dx][y + dy].place(bl.getColor());
            }
        }
    }
}

bool Game::checkForObstruction(const Tetromino& bl) const {
    const int x = bl.getX();
    const int y = bl.getY();
    for (int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
        for (int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
            // If there is a tetromino at that position
            if (bl.isFilledAt(dx, dy)) {  // Only check squares the tetromino fills
                // Check that the piece does not leave the game board
                if (!s_isOnBoard(x + dx, y + dy)) {
                    return true;
                }
                // See if there is a collision at that specific square.
                if (m_board[x + dx][y + dy].isPlaced()) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::createPreview() {
    if (!m_showPreview) {
        return;
    }

    m_tetrominoPreview = m_tetromino;
    while (
        !checkForObstruction(Tetromino::testMove(m_tetrominoPreview, tetris::Direction::South))) {
        m_tetrominoPreview.move(tetris::Direction::South);
    }
}

void Game::dropTetromino() {
    while (!checkForObstruction(Tetromino::testMove(m_tetromino, tetris::Direction::South))) {
        m_tetromino.move(tetris::Direction::South);
        m_score += 1;
    }
    placeTetromino();
}

void Game::update(tetris::Control keyPressed) {
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true;
        return;
    }

    switch (keyPressed) {
        case tetris::Control::NONE:
        case tetris::Control::PAUSE:
        case tetris::Control::QUIT:
            throw std::invalid_argument("Key is not handled in process function");
        case tetris::Control::DROP:
            dropTetromino();
            break;
        case tetris::Control::HOLD:
            if (!m_hold) {
                m_hold = std::optional<Tetromino>(m_tetromino);
                m_hold->hold();
                createNewTetromino();
            } else {
                if (m_tetromino.hasBeenHeld()) {
                    break;
                }
                // TODO use std::swap here std::swap(m_tetromino, m_hold);
                Tetromino tmp = std::move(m_hold.value());
                m_hold = std::optional<Tetromino>(std::move(m_tetromino));
                m_hold->hold();
                m_tetromino = std::move(tmp);
            }
            break;
        case tetris::Control::TOGGLE_PREVIEW:
            m_showPreview = !m_showPreview;
            break;
        case tetris::Control::ROTATE:
        case tetris::Control::RIGHT:
        case tetris::Control::DOWN:
        case tetris::Control::LEFT:
            const auto direction = tetris::ControlTools::controlToDirection(keyPressed);
            if (!checkForObstruction(Tetromino::testMove(m_tetromino, direction))) {
                m_tetromino.move(direction);
            }
            break;
    }
    createPreview();
}

void Game::placeTetromino() {
    m_tetrominoJustPlaced = true;
    addTetrominoToBoard(m_tetromino);
    removeCompleteRows();
    updateLevel();
    createNewTetromino();
    createPreview();
}

void Game::updateLevel() {
    const size_t newLevel = std::min(m_linesCleared / 10, static_cast<size_t>(tetris::MAX_LEVEL));
    if (m_level == newLevel) {
        return;
    }
    // Level changed, update level and game speed
    m_level = newLevel;
    updateSpeed();
}

void Game::updateSpeed() {
    const auto frameOn60 = (m_level < 9)    ? 48 - (5 * m_level)
                           : (m_level == 9) ? 5
                           : (m_level < 13) ? 4
                           : (m_level < 16) ? 3
                           : (m_level < 19) ? 2
                           : (m_level < 29) ? 1
                                            : 0;

    // This removes the correlation between fps and game speed.
    m_framesPerTick = static_cast<size_t>((static_cast<double>(frameOn60) + 0.5) /
                                          (60 * tetris::frameDuration.count()));
}

void Game::removeCompleteRows() {
    // Check how many rows and what rows to remove
    int rowsRemoved = 0;
    for (int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        int rowSum = 0;
        for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            if (m_board[x][y].isPlaced()) {
                rowSum += 1;
            }
        }
        // If all pieces in the row are covered
        if (rowSum == tetris::BOARD_WIDTH) {
            ++rowsRemoved;
            removeRow(y);
        }
    }
    switch (rowsRemoved) {
        case 0:
            return;
        case 1:
            m_score += 40 * (m_level + 1);
            break;
        case 2:
            m_score += 100 * (m_level + 1);
            break;
        case 3:
            m_score += 300 * (m_level + 1);
            break;
        case 4:
            m_score += 1200 * (m_level + 1);
            break;
        default:
            abort();
    }
    m_linesCleared += rowsRemoved;
}

void Game::removeRow(int index) {
    for (int y = 0; y <= index - 1; ++y) {
        for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            m_board[x][index - y].replace(m_board[x][index - y - 1]);
        }
    }
}

void Game::createNewTetromino() {
    m_tetromino = std::move(m_next);
    m_next = Tetromino();
}

// Templated render functions
template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Game::renderPauseScreen() const {
    UI<screenInterface>::renderPauseScreen(m_score, m_linesCleared, m_level);
}

template <typename screenInterface>
    requires Screen::ScreenInterface<screenInterface>
void Game::render() const {
    // Draw placed blocks board
    for (int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        for (int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            if (m_board[x][y].isPlaced()) {
                screenInterface::addCharAtBoard('B', x, y, m_board[x][y].getColor());
            }
        }
    }

    // Draw preview
    if (m_showPreview) {
        m_tetrominoPreview.render<screenInterface>(true);
    }

    // Draw current tetromino
    m_tetromino.render<screenInterface>();

    // Draw UI
    UI<screenInterface>::render(m_hold, m_next, m_score, m_linesCleared, m_level);
}

#include "screenTypeSelector.hpp"

template void Game::render<ScreenType>() const;
template void Game::renderPauseScreen<ScreenType>() const;
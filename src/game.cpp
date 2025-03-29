#include <iostream>
#include <cassert>

#include <game.hpp>
#include <ui.hpp>

#include <ScreenToUse.hpp>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
Game<screenInterface>::Game() {
    m_hold = std::nullopt;
    if (m_showPreview) {
        createPreview();   
    }

    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            m_board[x][y] = Square();
        }
    }
}

// TODO: Optimize
template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::tick() {
    // If the tetromino that is going to move is already tetrominoed
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true; // Game over
        return;
    }
    
    // See if we can move the tetromino down one if not place it.
    if (checkForObstruction(Tetromino<screenInterface>::testTick(m_tetromino))) {
        placeTetromino();
    } else {
        m_tetromino.tick();
    }
    
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
bool Game<screenInterface>::wasTetrominoJustPlaced() const {
    return m_tetrominoJustPlaced;
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::addTetrominoToBoard(const Tetromino<screenInterface> &bl) {
    const int x = bl.getX();
    const int y = bl.getY();
    for(int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
        for(int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
            if (bl.isFilledAt(dx, dy)) {
                if (isOnBoard(x + dx,y + dy)) {
                    m_board[x + dx][y + dy].place(bl.getColor());
                }
            }
        }
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
bool Game<screenInterface>::checkForObstruction(const Tetromino<screenInterface>& bl) const {
    const int x = bl.getX();
    const int y = bl.getY();
    for(int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
        for(int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
            // If there is a tetromino at that position
            if (bl.isFilledAt(dx, dy)) { // Only check squares the tetromino fills 
                //Check that the piece does not leave the game board
                if (!isOnBoard(x + dx,y + dy)) {
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

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::createPreview() {
    m_tetrominoPreview = m_tetromino;
    while(!checkForObstruction(Tetromino<screenInterface>::testMove(m_tetrominoPreview, tetris::Direction::South))) {
        m_tetrominoPreview.move(tetris::Direction::South);
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::dropTetromino() {
    while(!checkForObstruction(Tetromino<screenInterface>::testMove(m_tetromino, tetris::Direction::South))) {
        m_tetromino.move(tetris::Direction::South);
        m_score += 1;
    }
    placeTetromino();
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
bool Game<screenInterface>::isGameOver() const {
    return m_isGameOver;
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::update(tetris::Control keyPressed) {
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true; //Game over
        return;
    }

    switch (keyPressed)
    {
        case tetris::Control::NONE:
        case tetris::Control::PAUSE_KEY:
            break;
        case tetris::Control::QUIT_KEY:
            m_isGameOver = true; //Game over
            return;
        case tetris::Control::DROP_KEY:
            dropTetromino();
            break;
        case tetris::Control::HOLD_KEY:
            if (!m_hold) {
                m_hold = std::optional<Tetromino<screenInterface>>(m_tetromino);
                m_hold->hold();
                createNewTetromino();
            } else {
                if (m_tetromino.hasBeenHeld()) {
                    break; 
                }
                //TODO use std::swap here std::swap(m_tetromino, m_hold);
                Tetromino<screenInterface> tmp = std::move(m_hold.value());
                m_hold = std::optional<Tetromino<screenInterface>>(std::move(m_tetromino));
                m_hold->hold();
                m_tetromino = std::move(tmp);
            }
            break;
        case tetris::Control::TOGGLE_PREVIEW_KEY:
            m_showPreview = !m_showPreview;
            break;
        case tetris::Control::ROTATE_TETROMINO_KEY:
        case tetris::Control::MOVE_RIGHT_KEY:
        case tetris::Control::MOVE_DOWN_KEY:
        case tetris::Control::MOVE_LEFT_KEY:
            const auto direction = tetris::ControlTools::controlToDirection(keyPressed);
            if (!checkForObstruction(Tetromino<screenInterface>::testMove(m_tetromino, direction))) {
                m_tetromino.move(direction);
            }
            break;
    }

    if (m_showPreview) {
        createPreview();   
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
std::string Game<screenInterface>::getResult() const {
    return std::string("Game over \nResult:\nLines cleared:") + std::to_string(m_linesCleared) + "\nScore: " + std::to_string(m_score);

}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::placeTetromino() {
    m_tetrominoJustPlaced = true;
    addTetrominoToBoard(m_tetromino);
    removeCompleteRows();
    updateLevel();
    createNewTetromino();
    if (m_showPreview) {
        createPreview();   
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::updateLevel() {
    m_level = std::min(static_cast<int>(m_linesCleared/10),  tetris::MAX_LEVEL);
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
int Game<screenInterface>::getFramesPerTick() const {

    const int frameOn60 = 
        (m_level < 9) ? 48 - (5 * m_level) : 
        (m_level == 9) ? 5 : 
        (m_level < 13) ? 4 :
        (m_level < 16) ? 3 :
        (m_level < 19) ? 2 :
        (m_level < 29) ? 1 : 0;

    //This removes the correlation between fps and game speed.
    return static_cast<int>((frameOn60 + 0.5) / (60 * tetris::frameDuration.count()));
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::removeCompleteRows() {
    // Check how many (for score) rows and what rows to remove
    int rowsRemoved = 0;
    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        int rowSum = 0;
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
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
    switch (rowsRemoved)
    {
        case 0:
            break;
        case 1:
            m_score += 40*(m_level+1);
            break;
        case 2:
            m_score += 100*(m_level+1);
            break;
        case 3:
            m_score += 300*(m_level+1);
            break;
        case 4:
            m_score += 1200*(m_level+1);
            break;
        default:
            break;
    }
    m_linesCleared += rowsRemoved;
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::removeRow(int index) {
    for(int y = 0; y <= index-1; ++y) {
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            m_board[x][index-y].replace(m_board[x][index-y-1]);
        }
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::createNewTetromino() {
    m_tetromino = std::move(m_next);
    m_next = Tetromino<screenInterface>();
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::draw() const {
    screenInterface::clearScreen(); // Clear the screen
    //Draw board
    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            if (m_board[x][y].isPlaced()) {
                screenInterface::addCharAtBoard('B', x, y,m_board[x][y].getColor());
            }
        }
    }
    
    if (m_showPreview) {
        m_tetrominoPreview.draw(true);
    }
    
    m_tetromino.draw();
    // Draw UI
    UI<screenInterface>::draw(m_hold, m_next, m_score, m_linesCleared, m_level);
    screenInterface::redrawScreen(); // Redraw the screen
}
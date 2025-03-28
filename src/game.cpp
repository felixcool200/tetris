#include <iostream>
#include <cassert>

#include <game.hpp>
#include <ui.hpp>

#include <ScreenToUse.hpp>

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
Game<screenInterface>::Game() {
    updateSpeed();
    createPreview();
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::tick() {

    // The end of a tick is where we check if we are done, this gives the player 
    // a chance to recover even when the tetromino is touching other blocks
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true;
        return;
    }
    
    // See if we can move the tetromino down one if not place it.
    if (checkForObstruction(Tetromino<screenInterface>::testTick(m_tetromino))) {
        placeTetromino();
    } else {
        m_tetromino.tick();
    }
    
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
bool Game<screenInterface>::wasTetrominoJustPlaced() const {
    return m_tetrominoJustPlaced;
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::addTetrominoToBoard(const Tetromino<screenInterface> &bl) {
    const int x = bl.getX();
    const int y = bl.getY();
    for(int dy = 0; dy < tetris::SHAPESIZE; ++dy) {
        for(int dx = 0; dx < tetris::SHAPESIZE; ++dx) {
            if (bl.isFilledAt(dx, dy) && isOnBoard(x + dx,y + dy)) {
                m_board[x + dx][y + dy].place(bl.getColor());
            }
        }
    }
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
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

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::createPreview() {

    if (!m_showPreview) {
        return;   
    }

    m_tetrominoPreview = m_tetromino;
    while(!checkForObstruction(Tetromino<screenInterface>::testMove(m_tetrominoPreview, tetris::Direction::South))) {
        m_tetrominoPreview.move(tetris::Direction::South);
    }
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::dropTetromino() {
    while(!checkForObstruction(Tetromino<screenInterface>::testMove(m_tetromino, tetris::Direction::South))) {
        m_tetromino.move(tetris::Direction::South);
        m_score += 1;
    }
    placeTetromino();
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
bool Game<screenInterface>::isGameOver() const {
    return m_isGameOver;
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::update(tetris::Control keyPressed) {
    m_tetrominoJustPlaced = false;
    if (checkForObstruction(m_tetromino)) {
        m_isGameOver = true;
        return;
    }

    switch (keyPressed)
    {
        case tetris::Control::NONE:
        case tetris::Control::PAUSE_KEY:
            break;
        case tetris::Control::QUIT_KEY:
            m_isGameOver = true;
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
    createPreview();   
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
std::string Game<screenInterface>::getResult() const {
    return std::string("Game over \nResult:\nLines cleared:") + std::to_string(m_linesCleared) + "\nScore: " + std::to_string(m_score);
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::placeTetromino() {
    m_tetrominoJustPlaced = true;
    addTetrominoToBoard(m_tetromino);
    removeCompleteRows();
    updateLevel();
    createNewTetromino();
    createPreview();
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::updateLevel() {
    const unsigned int newLevel = std::min(static_cast<int>(m_linesCleared/10),  tetris::MAX_LEVEL);
    if(m_level == newLevel) {
        return;
    }
    // Level changed, update level and game speed
    m_level = newLevel;
    updateSpeed();
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::updateSpeed() {
    const int frameOn60 = 
        (m_level < 9) ? 48 - (5 * m_level) : 
        (m_level == 9) ? 5 : 
        (m_level < 13) ? 4 :
        (m_level < 16) ? 3 :
        (m_level < 19) ? 2 :
        (m_level < 29) ? 1 : 0;

    //This removes the correlation between fps and game speed.
    m_framesPerTick = static_cast<int>((frameOn60 + 0.5) / (60 * tetris::frameDuration.count()));
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
int Game<screenInterface>::getFramesPerTick() const {
    return m_framesPerTick;
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::removeCompleteRows() {
    // Check how many rows and what rows to remove
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
            return;
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
            abort();
    }
    m_linesCleared += rowsRemoved;
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::removeRow(int index) {
    for(int y = 0; y <= index-1; ++y) {
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            m_board[x][index-y].replace(m_board[x][index-y-1]);
        }
    }
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::createNewTetromino() {
    m_tetromino = std::move(m_next);
    m_next = Tetromino<screenInterface>();
}

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
void Game<screenInterface>::draw() const {

    // Clear the screen
    screenInterface::clearScreen();
    
    // Draw placed blocks board
    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y) {
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x) {
            if (m_board[x][y].isPlaced()) {
                screenInterface::addCharAtBoard('B', x, y,m_board[x][y].getColor());
            }
        }
    }
    
    // Draw preview
    if (m_showPreview) {
        m_tetrominoPreview.draw(true);
    }
    
    // Draw current tetromino
    m_tetromino.draw();

    // Draw UI
    UI<screenInterface>::draw(m_hold, m_next, m_score, m_linesCleared, m_level);
    
    // Redraw the screen
    screenInterface::redrawScreen();
}
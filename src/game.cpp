#include <iostream>
#include <cassert>

#include <game.hpp>


Game::Game(){
    m_hold = Tetromino(-2);
    if(m_showPreview){
        createPreview();   
    }

    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y){
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x){
            m_board[x][y] = Square();
        }
    }
}

// TODO: Optimize
void Game::tick(){
    // If the tetromino that is going to move is already tetrominoed
    m_tetrominoJustPlaced = false;
    if(checkForObstruction(m_tetromino)){
        m_isGameOver = true; // Game over
        return;
    }
    
    //See if we can move the tetromino down one if not place it.
    if(checkForObstruction(testTick(m_tetromino)))
        placeTetromino();
    else
        m_tetromino.tick();
}

bool Game::wasTetrominoJustPlaced() const{
    return m_tetrominoJustPlaced;
}

void Game::addTetrominoToBoard(Tetromino &bl){
    const int x = bl.getX();
    const int y = bl.getY();
    for(int dy = 0; dy < tetris::SHAPESIZE; ++dy){
        for(int dx = 0; dx < tetris::SHAPESIZE; ++dx){
            if(bl.isFilledAt(dx, dy)){
                if(isOnBoard(x + dx,y + dy)){
                    m_board[x + dx][y + dy].place(bl.getColor());
                }
            }
        }
    }
}

bool Game::checkForObstruction(Tetromino bl){
    const int x = bl.getX();
    const int y = bl.getY();
    for(int dy = 0; dy < tetris::SHAPESIZE; ++dy){
        for(int dx = 0; dx < tetris::SHAPESIZE; ++dx){
            // If there is a tetromino at that position
            if(bl.isFilledAt(dx, dy)){ // Only check squares the tetromino fills 
                //Check that the piece does not leave the game board
                if(!isOnBoard(x + dx,y + dy)){
                    return true;
                }
                // See if there is a collision at that specific square.
                if(m_board[x + dx][y + dy].isPlaced()){
                    return true;
                }
            }
        }
    }
    return false;
}

void Game::createPreview(){
    m_tetrominoPreview = m_tetromino;
    while(!checkForObstruction(testMove(m_tetrominoPreview, tetris::Control::MOVE_DOWN_KEY))){
        m_tetrominoPreview.move(tetris::Control::MOVE_DOWN_KEY);
    }
}

void Game::dropTetromino(){
    while(!checkForObstruction(testMove(m_tetromino, tetris::Control::MOVE_DOWN_KEY))){
        m_tetromino.move(tetris::Control::MOVE_DOWN_KEY);
        m_score += 1;
    }
    placeTetromino();
}
bool Game::isGameOver() const{
    return m_isGameOver;
}

void Game::update(tetris::Control ch){
    m_tetrominoJustPlaced = false;
    if(checkForObstruction(m_tetromino)){
        m_isGameOver = true; //Game over
        return;
    }

    switch (ch)
    {
    case tetris::Control::QUIT_KEY:
        m_isGameOver = true; //Game over
        return;
    case tetris::Control::DROP_KEY:
        dropTetromino();
        break;
    case tetris::Control::HOLD_KEY:
        if(m_hold.getY() == -2){ // Same as never been held (no real tetromino will have -2 in Y)
            m_hold = std::move(m_tetromino);
            m_hold.hold();
            createNewTetromino();
        }else{
            if(!m_tetromino.hasBeenHeld()){
                Tetromino tmp = std::move(m_hold);
                m_hold = std::move(m_tetromino);
                m_hold.hold();
                m_tetromino = std::move(tmp);
            }
        }
        break;
    case tetris::Control::TOGGLE_PREVIEW_KEY:
        m_showPreview = !m_showPreview;
        break;
    default:
        if(!checkForObstruction(testMove(m_tetromino,ch))){
            m_tetromino.move(ch);
        }
        break;
    }
    if(m_showPreview){
        createPreview();   
    }
}

Tetromino Game::getHold() const{
    return m_hold;
}

Tetromino Game::getNext() const{
    return m_next;
}

unsigned int Game::getScore() const{
    return m_score;
}

unsigned int Game::getLines() const{
    return m_linesCleared;
}

unsigned short Game::getLevel() const{
    return m_level;
}

bool Game::isOnBoard(int x, int y){
    return ((x <= tetris::BOARD_WIDTH - 1) && (x >= 0) && (y <= tetris::BOARD_HEIGHT - 1) && (y >= 0));
}

void Game::placeTetromino(){
    m_tetrominoJustPlaced = true;
    addTetrominoToBoard(m_tetromino);
    removeCompleteRows();
    updateLevel();
    createNewTetromino();
    if(m_showPreview)
        createPreview();   
}

void Game::updateLevel(){
    m_level = std::min(static_cast<int>(m_linesCleared/10),  tetris::MAX_LEVEL);
}

int Game::getFramesPerTick() const{

    const int frameOn60 = 
        (m_level < 9) ? 48 - (5 * m_level) : 
        (m_level == 9) ? 5 : 
        (m_level < 13) ? 4 :
        (m_level < 16) ? 3 :
        (m_level < 19) ? 2 :
        (m_level < 29) ? 1 : 0;

    //This removes the correlation between fps and game speed.
    return (frameOn60 + 0.5)/(60*std::chrono::duration_cast<std::chrono::seconds>(tetris::frameDuration).count());
}

void Game::removeCompleteRows(){
    // Check how many (for score) rows and what rows to remove
    int rowsRemoved = 0;
    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y){
        int rowSum = 0;
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x){
            if(m_board[x][y].isPlaced()){
                rowSum += 1;
            }
        }
        // If all pieces in the row are covered
        if(rowSum == tetris::BOARD_WIDTH){
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
    
    //std::clog << "COMPLETED COUNTING" << std::endl;
    //HERE REMOVE ROWS ONE BY ONE AND MOVE ALL OTHER ROWS DOWN
    // OPTIMIZE BY REMOVING MULTIPE ROWS
}

void Game::removeRow(int index){
    for(int y = 0; y <= index-1; ++y){
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x){
            //std::cout << "x:" << x << " y: "<< y << std::endl;
            m_board[x][index-y].replace(m_board[x][index-y-1]);
        }
    }
}

void Game::createNewTetromino(){
    m_tetromino = std::move(m_next);
    m_next = Tetromino();
}

void Game::draw() const{
    //Draw board
    for(int y = 0; y < tetris::BOARD_HEIGHT; ++y){
        for(int x = 0; x < tetris::BOARD_WIDTH; ++x){
            if(m_board[x][y].isPlaced()){
                ScreenHandler::addCharAtBoard('B', x, y,m_board[x][y].getColor());
            }
        }
    }

    if(m_showPreview){
        m_tetrominoPreview.draw(true);
    }

    m_tetromino.draw();    
}

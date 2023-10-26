#include "../include/game.hpp"
#include "../include/square.hpp"
#include "../include/tetromino.hpp"
#include "../include/screenHandler.hpp"
#include <iostream>

Game::Game(){
    m_tetromino = Tetromino();
    m_hold = Tetromino(-2);
    m_next = Tetromino();
    m_score = 0;
    m_level = 0;
    m_linesCleared = 0;
    m_showPreview = true;
    m_tetrominoJustPlaced = false;
    if(m_showPreview){
        createPreview();   
    }

    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            m_board[x][y] = Square();
        }
    }
}

// TODO: Optimize
bool Game::tick(){
    // If the tetromino that is going to move is already tetrominoed
    m_tetrominoJustPlaced = false;
    if(checkForObstruction(m_tetromino)){
        return true; // Game over
    }
    //See if we can move the tetromino down one if not place it.
    if(checkForObstruction(testTick(m_tetromino))){
        placeTetromino();
    }else{   
        m_tetromino.tick();
    }
    return false; //Game continues
}

bool Game::wasTetrominoJustPlaced(){
    return m_tetrominoJustPlaced;
}

void Game::addTetrominoToBoard(Tetromino &bl){
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            if(bl.isFilledAt(dx, dy)){
                if(isOnBoard(x + dx,y + dy)){
                    m_board[x + dx][y + dy].place(bl.getColor());
                }
            }
        }
    }
}

/*
int Game::amountOfRowsFilled(){
    int numberOfRowsFilled = 0;
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        int rowSum = 0;
        for(int j = 0; j < BOARD_WIDTH; ++j){
            if(m_board[j][i].isPlaced()){
                rowSum += 1;
            }
        }
        // If all pieces of the current row are covered
        if(rowSum == BOARD_WIDTH){
            numberOfRowsFilled += 1;
        }
    }
    return numberOfRowsFilled;
}

bool Game::checkForFinalLocation(Tetromino bl){
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a tetromino at that position
            if(bl.isFilledAt(dx, dy)){
                //And if we move one more tetromino there is another tetromino there
                if(isOnBoard(x + dx,y + dy)){ // Remove? is it unnecessary?
                    if(m_board[x + dx][y + dy + 1] || y + dy == BOARD_HEIGHT - 1){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}*/

bool Game::checkForObstruction(Tetromino bl){
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
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
    while(!checkForObstruction(testMove(m_tetrominoPreview,'s'))){
        m_tetrominoPreview.move('s');
    }
}

void Game::dropTetromino(){
    while(!checkForObstruction(testMove(m_tetromino,'s'))){
        m_tetromino.move('s');
        m_score += 1;
    }
    placeTetromino();
}

bool Game::update(char ch){
    m_tetrominoJustPlaced = false;
    if(checkForObstruction(m_tetromino)){
        return true; //Game over
    }

    switch (ch)
    {
    case QUIT_KEY:
        return true; //Game over
        break; //Unnecessary but makes it easier to read
    case DROP_KEY:
        dropTetromino();
        break;
    case HOLD_KEY:
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
    case TOGGLE_PREVIEW_KEY:
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
    return false; //Game continues
}

Tetromino Game::getHold(){
    return m_hold;
}

Tetromino Game::getNext(){
    return m_next;
}

unsigned int Game::getScore(){
    return m_score;
}

unsigned int Game::getLines(){
    return m_linesCleared;
}

unsigned short Game::getLevel(){
    return m_level;
}

bool Game::isOnBoard(int x, int y){
    return ((x <= BOARD_WIDTH - 1) && (x >= 0) && (y <= BOARD_HEIGHT - 1) && (y >= 0));
}

void Game::placeTetromino(){
    m_tetrominoJustPlaced = true;
    //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
    addTetrominoToBoard(m_tetromino);
    removeCompleteRows();
    updateLevel();
    //checkForGameOver();
    createNewTetromino();
    if(m_showPreview){
        createPreview();   
    }
}


void Game::updateLevel(){
    int level = static_cast<int>(m_linesCleared/10);
    
    if (level < MAX_LEVEL){
        m_level = level;
    }else{
        m_level = MAX_LEVEL;
    }
}

int Game::getFramesPerTick(){

    int frameOn60 = 0;
    //LEVEL 0-8
    if(m_level < 9){
        frameOn60 = 48-(5*m_level);
    }
    //LEVEL 9
    else if(m_level < 10){
        frameOn60 = 5;
    }
    //LEVEL 10-12
    else if(m_level < 13){ 
        frameOn60 = 4;
    }
    //LEVEL 13-15
    else if(m_level < 16){
        frameOn60 = 3;
    }
    //LEVEL 16-18
    else if(m_level < 19){
        frameOn60 = 2;
    }
    //LEVEL 19-28
    else if(m_level < 29){
        frameOn60 = 1;
    }
    else{
        frameOn60 = 0;
    }
    //This removes the correlation between fps and game speed.
    return (frameOn60 + 0.5)/(60*secoundsPerFrame);
}


void Game::removeCompleteRows(){
    // Check how many (for score) rows and what rows to remove
    int rowsRemoved = 0;
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        int rowSum = 0;
        for(int x = 0; x < BOARD_WIDTH; ++x){
            if(m_board[x][y].isPlaced()){
                rowSum += 1;
            }
        }
        // If all pieces in the row are covered
        if(rowSum == BOARD_WIDTH){
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
        for(int x = 0; x < BOARD_WIDTH; ++x){
            //std::cout << "x:" << x << " y: "<< y << std::endl;
            m_board[x][index-y].replace(m_board[x][index-y-1]);
        }
    }
}
/*
void Game::removeRows(int start,int stop){
    //std::clog << "COMPLETED REMOVE" << std::endl;
    
    if(rowIndexToRemove[0] == rowIndexToRemove[1] + 1){
        if(rowIndexToRemove[1] == rowIndexToRemove[2] + 1){
            if(rowIndexToRemove[2] == rowIndexToRemove[3] + 1){
                //TETRIS!!!!!!!!!!!
                removeRows(rowIndexToRemove[3],rowIndexToRemove[0]);
            }else{
                //Three Rows
                removeRows(rowIndexToRemove[2],rowIndexToRemove[0]);
            }
        }else{
            //Two Rows
        }
    }else{
        //One row
    }

}
*/
void Game::createNewTetromino(){
    m_tetromino = std::move(m_next);
    m_next = Tetromino();
    
}

void Game::draw(){
    //Draw board
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
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

#include "../include/board.hpp"
#include "../include/square.hpp"
#include "../include/block.hpp"
#include "../include/screenHandler.hpp"
#include <iostream>

Board::Board(){
    m_block = Block();
    m_hold = Block(-2);
    m_next = Block();
    m_score = 0;
    m_level = 0;
    m_linesCleared = 0;
    m_showPreview = true;
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            m_board[x][y] = Square();
        }
    }
    // TODO: REMOVE ALL BELOW ONLY FOR TEXTING
    for(int y = 0; y < 4; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            m_board[x][BOARD_HEIGHT-1-y].place(4);
            m_board[0][BOARD_HEIGHT-1-y].remove();
        }
    }
    m_gameOver = false;
    if(m_showPreview){
        createPreview();   
    }
}

// TODO: Optimize
void Board::tick(){
    // If the block that is going to move is already blocked
    m_blockJustPlaced = false;
    if(checkForObstruction(m_block)){
        m_gameOver = true;
    }
    /*if(checkForObstruction(m_block)){
        m_gameOver = true;
    }*/
    //See if we can move the block down one if not place it.
    if(checkForObstruction(testTick(m_block))){
        placeBlock();
    }else{   
        m_block.tick();
    }
}

bool Board::wasBlockJustPlaced(){
    return m_blockJustPlaced;
}


void Board::addBlockToBoard(Block bl){
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
int Board::amountOfRowsFilled(){
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

bool Board::checkForFinalLocation(Block bl){
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
            if(bl.isFilledAt(dx, dy)){
                //And if we move one more block there is another block there
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

bool Board::checkForObstruction(Block bl){
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
            if(bl.isFilledAt(dx, dy)){ // Only check if the block is 
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

void Board::createPreview(){
    m_blockPreview = m_block;
    while(!checkForObstruction(testMove(m_blockPreview,'s'))){
        m_blockPreview.move('s');
    }
}

void Board::update(char ch){
    m_blockJustPlaced = false;
    if(checkForObstruction(m_block)){
        m_gameOver = true;
        return;
    }

    switch (ch)
    {
    case ' ':
        while(!checkForObstruction(testMove(m_block,'s'))){
            m_block.move('s');
            m_score += 1;
            }
        placeBlock();
        break;
    case 'c':
        if(m_hold.getY() == -2){ // Same as never been held (no real block will have -2 in Y)
            m_hold = std::move(m_block);
            m_hold.hold();
            createNewBlock();
        }else{
            if(!m_block.hasBeenHeld()){
                Block tmp = m_hold;
                m_hold = std::move(m_block);
                m_hold.hold();
                m_block = tmp;
            }
        }
        break;
    case 'p':
        m_showPreview = !m_showPreview;
        break;
    default:
        if(!checkForObstruction(testMove(m_block,ch))){
            m_block.move(ch);
        }
        break;
    }
    if(m_showPreview){
        createPreview();   
    }
}

Block Board::getHold(){
    return m_hold;
}


Block Board::getNext(){
    return m_next;
}

unsigned int Board::getScore(){
    return m_score;
}

unsigned int Board::getLines(){
    return m_linesCleared;
}

bool Board::isOnBoard(int x, int y){
    return ((x <= BOARD_WIDTH - 1) && (x >= 0) && (y <= BOARD_HEIGHT - 1) && (y >= 0));
}

void Board::placeBlock(){
    m_blockJustPlaced = true;
    //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
    addBlockToBoard(m_block);
    removeCompleteRows();
    updateLevel();
    //checkForGameOver();
    createNewBlock();
}


bool Board::isGameOver(){
    return m_gameOver;
}

void Board::updateLevel(){
    int level = static_cast<int>(m_linesCleared/10);
    
    if (level < MAX_LEVEL){
        m_level = level;
    }else{
        m_level = MAX_LEVEL;
    }
}

//After level 10, the game speed only increases on levels 13, 16, 19, and 29, at which point the speed no longer increases. On level 29, pieces fall at 1 grid cell every frame, which is too fast for almost all players,

int Board::getFramesPerTick(){

    //LEVEL 0-8
    if(m_level < 9){
        return 48-(5*m_level);
    }
    //LEVEL 9
    else if(m_level < 10){
        return 5;
    }
    //LEVEL 10-12
    else if(m_level < 13){ 
        return 4;
    }
    //LEVEL 13-15
    else if(m_level < 16){
        return 3;
    }
    //LEVEL 16-18
    else if(m_level < 19){
        return 2;
    }
    //LEVEL 19-28
    else if(m_level < 29){
        return 1;
    }
    else{
        return 0;
    }
}


void Board::removeCompleteRows(){
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

void Board::removeRow(int index){
    for(int y = 0; y <= index-1; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            //std::cout << "x:" << x << " y: "<< y << std::endl;
            m_board[x][index-y].replace(m_board[x][index-y-1]);
        }
    }
}
/*
void Board::removeRows(int start,int stop){
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
void Board::createNewBlock(){
    m_block = std::move(m_next);
    m_next = Block();
}

void Board::draw(WINDOW*& screen){
    //Draw board
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            if(m_board[x][y].isPlaced()){
                ScreenHandler::addCharAtBoard('B', x, y,m_board[x][y].getColor(),screen);
            }
        }
    }

    m_block.draw(screen);    
    if(m_showPreview){
        m_blockPreview.draw(screen);
    }
}

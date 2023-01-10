#include "board.hpp"
#include "square.hpp"
#include "block.hpp"
#include "ScreenHandler.hpp"
#include <iostream>

Board::Board(){
    m_block = Block();
    m_hold = Block(-2);
    m_score = 0;
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
            m_hold = m_block;
            m_hold.hold();
            m_block = Block(true);
        }else{
            if(!m_block.hasBeenHeld()){
                Block tmp = m_hold;
                m_hold = m_block;
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

bool Board::isOnBoard(int x, int y){
    return ((x <= BOARD_WIDTH - 1) && (x >= 0) && (y <= BOARD_HEIGHT - 1) && (y >= 0));
}

void Board::placeBlock(){
    m_blockJustPlaced = true;
    //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
    addBlockToBoard(m_block);
    removeCompleteRows();
    //checkForGameOver();
    createNewBlock();
}


bool Board::isGameOver(){
    return m_gameOver;
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
    m_block = Block();
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

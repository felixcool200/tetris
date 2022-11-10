#include "board.h"
#include "block.h"
#include "ScreenHandler.h"
#include <iostream>

Board::Board(){
    m_block = Block();
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            m_board[x][y] = false;
        }
    }
    for(int y = 0; y < 2; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            m_board[x][BOARD_HEIGHT-1-y] = true;
        }
    }
    m_board[0][BOARD_HEIGHT-1] = false;
    m_board[0][BOARD_HEIGHT-2] = false;
}

void Board::tick(){
    m_block.tick();
}

void Board::addBlockToBoard(Block bl){
    //m_board[bl.getX() + 2][bl.getY() + 2] = true;
    //int matches = 0;
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            if(bl.getShape(dx, dy)){
                //matches++;
                //std::clog << "x:" << x+dx << " y: "<< y+dy << std::endl;
                m_board[x + dx][y + dy] = true;
            }
        }
    }
}

int Board::amountOfRowsFilled(){
    int numberOfRowsFilled = 0;
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        int rowSum = 0;
        for(int j = 0; j < BOARD_WIDTH; ++j){
            if(m_board[j][i]){
                rowSum += 1;
            }
        }
        // If all pieces are covered
        if(rowSum == BOARD_WIDTH){
            numberOfRowsFilled += 1;
        }
    }
    return numberOfRowsFilled;
}

bool Board::checkForFinalLocation(Block bl){
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
            if(bl.getShape(dx, dy)){
                //And if we move one more block there is another block there
                if(m_board[bl.getX() + dx][bl.getY() + dy + 1] || bl.getY() + dy >= BOARD_HEIGHT - 1){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::checkForObstruction(Block bl){
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
            if(bl.getShape(dx, dy)){
                if(bl.getX() + dx > 0 && bl.getX() + dx < BOARD_WIDTH - 1){
                    if(m_board[bl.getX() + dx][bl.getY() + dy]){
                        return true;
                    }
                }
            }
            if(bl.getShape(dx, dy) && (bl.getX() + dx < 0|| bl.getX() + dx > BOARD_WIDTH - 1)){
                return true;
            }
        }
    }
    return false;
}

void Board::update(int ch){
    if(!checkForObstruction(testMove(m_block,ch))){
        m_block.move(ch);
    }
    if(checkForFinalLocation(m_block)){
        //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
        addBlockToBoard(m_block);
        removeCompleteRows();
        //checkForGameOver();
        createNewBlock();
    }
}

void Board::removeCompleteRows(){
    // Check how many (for score) rows and what rows to remove
    int rowsRemoved = 0;
    int rowIndex = 0;
    int rowIndexToRemove[4] = {-1,-1,-1,-1};
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        int rowSum = 0;
        for(int x = 0; x < BOARD_WIDTH; ++x){
            if(m_board[x][y]){
                rowSum += 1;
            }
        }
        // If all pieces in the row are covered
        if(rowSum == BOARD_WIDTH){
            ++rowsRemoved;
            rowIndexToRemove[rowIndex] = y;
            ++rowIndex;
        }
    }
    //std::clog << "COMPLETED COUNTING" << std::endl;
    //HERE REMOVE ROWS ONE BY ONE AND MOVE ALL OTHER ROWS DOWN
    // OPTIMIZE BY REMOVING MULTIPE ROWS
    for(rowIndex = 0;rowIndex < rowsRemoved;++rowIndex){
        // OPTIMIZE BY REMOVING MULTIPE ROWS
        removeRow(rowIndexToRemove[rowIndex]);
    }
}

void Board::removeRow(int index){
    for(int y = 0; y <= index-1; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            //std::cout << "x:" << x << " y: "<< y << std::endl;
            m_board[x][index-y] = m_board[x][index-y-1];
        }
    }
}

void Board::removeRows(int start,int stop){
    //std::clog << "COMPLETED REMOVE" << std::endl;
    /*
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
    */
}

void Board::createNewBlock(){
    m_block = Block();
}

void Board::draw(WINDOW*& screen){
    for(int y = 0; y < BOARD_HEIGHT; ++y){
        for(int x = 0; x < BOARD_WIDTH; ++x){
            /*if(x >= 10){
                ScreenHandler::addCharAtBoard(screen,(x-10)+'0', x, y);
            }else{
                ScreenHandler::addCharAtBoard(screen,x+'0', x, y);
            }*/
            if(m_board[x][y]){
                ScreenHandler::addCharAtBoard(screen,'B', x, y);
            }
        }
    }
    m_block.draw(screen);
}
#include "board.h"
#include "block.h"
#include "ScreenHandler.h"

Board::Board(){
    m_block = Block();
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            m_board[j][i] = false;
        }
    }
}

void Board::tick(){
    m_block.tick();
}

void Board::addBlockToBoard(Block bl){
    m_board[bl.getX() + 2][bl.getY() + 2] = true;
    /*for(int i = 0; i < SHAPESIZE; ++i){
        for(int j = 0; j < SHAPESIZE; ++j){
            if(bl.getShape(bl.getX() + j, bl.getY() + i)){
                m_board[bl.getX() + j][bl.getY() + i] = true;
            }
        }
    }*/
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

bool Board::checkForCollision(Block bl){
    for(int i = 0; i < SHAPESIZE; ++i){
        for(int j = 0; j < SHAPESIZE; ++j){
            // If there is a block at that position
            if(bl.getShape(bl.getX() + j, bl.getY() + i)){
                //And if we move one more block there is another block there
                if(m_board[bl.getX() + j][bl.getY() + i + 1] || bl.getY() + i + 1 == BOARD_HEIGHT){
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::update(int ch){
    m_block.move(ch);
<<<<<<< HEAD
    m_block.update();
=======
    if(checkForCollision(m_block)){
        //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
        addBlockToBoard(m_block);
        createNewBlock();
    }
}

void Board::createNewBlock(){
    m_block = Block();
>>>>>>> 55d0b1e015c73c859648c99fd7a0aee26227e80a
}


void Board::draw(WINDOW*& screen){
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            if(m_board[j][i]){
                ScreenHandler::addCharAtBoard(screen,'B',j,i);
            }
        }
    }
    m_block.draw(screen);
}
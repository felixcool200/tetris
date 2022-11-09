#include "board.h"
#include "block.h"
#include "ScreenHandler.h"
#include <iostream>

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
    //m_board[bl.getX() + 2][bl.getY() + 2] = true;
    //int matches = 0;
    int x = bl.getX();
    int y = bl.getY();
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            if(bl.getShape(dx, dy)){
                //matches++;
                std::clog << "x:" << x+dx << " y: "<< y+dy << std::endl;
                m_board[x + dx][y + dy] = true;
            }
        }
    }
    /*endwin();
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            if(m_board[j][i]){
                std::clog << "x:" << j << " y: "<< i << std::endl;
            }
        }
    }
    int i = 1/0;*/
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
    for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
            if(bl.getShape(dx, dy)){
                //And if we move one more block there is another block there
                if(m_board[bl.getX() + dx][bl.getY() + dy + 1] || bl.getY() + dy + 1 == BOARD_HEIGHT - 1){
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::update(int ch){
    m_block.move(ch);
    if(checkForCollision(m_block)){
        //ScreenHandler::addStringAt(stdscr,std::string("Collision detected"),0,0);
        addBlockToBoard(m_block);
        createNewBlock();
    }
}

void Board::createNewBlock(){
    m_block = Block();
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
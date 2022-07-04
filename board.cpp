#include "board.h"
#include "block.h"

Board::Board(){
    m_block = Block(0,0);
    for(int i = 0; i < BOARD_HEIGHT; ++i){
        for(int j = 0; j < BOARD_WIDTH; ++j){
            m_board[j][i] = false;
        }
    }
}
void Board::addPiece(Block bl){

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

void Board::update(int ch){
    m_block.move(ch);
    m_block.update();
}

void Board::draw(WINDOW*& screen){
    m_block.draw(screen);
    return;
    //waddstr(screen,"hej");
    //mvwaddch(screen, 0, 0, '#');
    for(int i = 0; i < BOARD_WIDTH; ++i){
        for(int j = 0; j < BOARD_HEIGHT; ++j){
            if(m_block.getX() == i && m_block.getY() == j){
                
            }
        }
    }
}
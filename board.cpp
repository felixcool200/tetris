#include "board.h"

Board::Board(){}
void Board::addPiece(Block bl){}
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
}

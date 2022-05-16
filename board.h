#pragma once
#include "block.h"

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

class Board{
    private:
        bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
    public:
        Board();
        void addPiece(Block bl);
        int amountOfRowsFilled();
        void update(int ch);
};
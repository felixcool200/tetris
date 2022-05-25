#pragma once
#include "constants.h"
#include "block.h"
#include <ncurses.h>

class Board{
    private:
        bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
    public:
        Board();
        void addPiece(Block bl);
        int amountOfRowsFilled();
        void update(int ch);
        void draw(WINDOW*& screen);
};
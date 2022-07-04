#pragma once
#include "constants.h"
#include "block.h"
#include <ncurses.h>

class Board{
    private:
        bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
        bool checkForCollision(Block bl);
        void addBlockToBoard(Block bl);
        int amountOfRowsFilled();
        void createNewBlock();
    public:
        Board();
        void tick();
        void update(int ch = -1);
        void draw(WINDOW*& screen);
};
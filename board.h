#pragma once
#include "constants.h"
#include "block.h"
#include <ncurses.h>

class Board{
    private:
        bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
        bool checkForFinalLocation(Block bl);
        bool checkForObstruction(Block bl);
        void addBlockToBoard(Block bl);
        void removeCompleteRows();
        int amountOfRowsFilled();
        void createNewBlock();
        void removeRow(int index);
        void removeRows(int start,int stop);

    public:
        Board();
        void tick();
        void update(int ch = -1);
        void draw(WINDOW*& screen);
};
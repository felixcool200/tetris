#pragma once
#include "constants.h"
#include "block.h"
#include "square.h"
#include <ncurses.h>

class Board{
    private:
        //bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Square m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
        bool m_gameOver;
        
        //bool checkForFinalLocation(Block bl);
        bool checkForObstruction(Block bl);
        bool isOnBoard(int x,int y);
        
        int amountOfRowsFilled();
        
        void placeBlock();
        void checkForGameOver();
        void addBlockToBoard(Block bl);
        void removeCompleteRows();
        void createNewBlock();
        void removeRow(int index);
        void removeRows(int start,int stop);

    public:
        Board();
        bool isGameOver();
        void tick();
        void update(int ch = -1);
        void draw(WINDOW*& screen);
};
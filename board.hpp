#pragma once
#include "constants.hpp"
#include "block.hpp"
#include "square.hpp"
#include <ncurses.h> // To get WINDOW*&
class Board{
    private:
        //bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Square m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
        bool m_gameOver;
        bool m_blockJustPlaced;
        Block m_hold;
        Block m_blockPreview;
        unsigned long m_score;
        bool m_showPreview;
        
        //bool checkForFinalLocation(Block bl);
        bool checkForObstruction(Block bl);
 
        //int amountOfRowsFilled();

        void createPreview();        
        void placeBlock();
        void addBlockToBoard(Block bl);
        void removeCompleteRows();
        void createNewBlock();
        void removeRow(int index);
        /*void removeRows(int start,int stop);*/

    public:
        Board();
        bool isGameOver();
        void tick();
        void update(char ch);
        void draw(WINDOW*& screen);
        Block getHold();
        static bool isOnBoard(int x,int y);
        bool wasBlockJustPlaced();
};

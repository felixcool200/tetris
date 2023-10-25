#pragma once
#include "constants.hpp"
#include "block.hpp"
#include "square.hpp"
class Board{
    private:
        //bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Square m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Block m_block;
        bool m_gameOver;
        bool m_blockJustPlaced;
        Block m_hold;
        Block m_next;   
        Block m_blockPreview;
        unsigned int m_score;
        unsigned int m_linesCleared;
        unsigned short m_level;
        bool m_showPreview;
        
        //bool checkForFinalLocation(Block bl);
        bool checkForObstruction(Block bl);
 
        //int amountOfRowsFilled();

        void createPreview();     
        void dropBlock();   
        void placeBlock();
        void addBlockToBoard(Block &bl);
        void removeCompleteRows();
        void createNewBlock();
        void removeRow(int index);
        /*void removeRows(int start,int stop);*/

    public:
        Board();
        bool isGameOver();
        void tick();
        int getFramesPerTick();
        void updateLevel();
        void update(char ch);
        void draw();
        Block getHold();
        Block getNext();
        unsigned int getScore();
        unsigned int getLines();
        unsigned short getLevel();
        static bool isOnBoard(int x,int y);
        bool wasBlockJustPlaced();
};

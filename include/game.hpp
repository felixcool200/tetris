#pragma once

#include "constants.hpp"
#include "tetromino.hpp"
#include "square.hpp"

class Game{
    private:
        //bool m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Square m_board[BOARD_WIDTH][BOARD_HEIGHT];
        Tetromino m_tetromino;
        bool m_gameOver;
        bool m_tetrominoJustPlaced;
        Tetromino m_hold;
        Tetromino m_next;   
        Tetromino m_tetrominoPreview;
        unsigned int m_score;
        unsigned int m_linesCleared;
        unsigned short m_level;
        bool m_showPreview;
        
        //bool checkForFinalLocation(Tetromino bl);
        bool checkForObstruction(Tetromino bl);
 
        //int amountOfRowsFilled();

        void createPreview();     
        void dropTetromino();   
        void placeTetromino();
        void addTetrominoToBoard(Tetromino &bl);
        void removeCompleteRows();
        void createNewTetromino();
        void removeRow(int index);
        void updateLevel();
        /*void removeRows(int start,int stop);*/

    public:
        Game();
        bool isGameOver();
        int getFramesPerTick();
        int update(char ch);
        void tick();
        void draw();
        Tetromino getHold();
        Tetromino getNext();
        unsigned int getScore();
        unsigned int getLines();
        unsigned short getLevel();
        static bool isOnBoard(int x,int y);
        bool wasTetrominoJustPlaced();
};

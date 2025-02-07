#pragma once
#include <array>

#include <common.hpp>
#include <tetromino.hpp>
#include <square.hpp>
#include <screenHandler.hpp>

class Game{
    private:
        std::array<std::array<Square,tetris::BOARD_WIDTH>,tetris::BOARD_HEIGHT> m_board;
        Tetromino m_tetromino;
        Tetromino m_hold;
        Tetromino m_next;   
        Tetromino m_tetrominoPreview;
        unsigned int m_score = 0;
        unsigned int m_linesCleared = 0;
        unsigned short m_level = 0;
        bool m_showPreview = true;
        bool m_isGameOver = false;
        bool m_tetrominoJustPlaced = true;
        
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
        int getFramesPerTick() const;
        void update(tetris::Control ch);
        void tick();
        void draw() const;
        Tetromino getHold() const;
        Tetromino getNext() const;
        unsigned int getScore() const;
        unsigned int getLines() const;
        unsigned short getLevel() const;
        bool wasTetrominoJustPlaced() const;
        bool isGameOver() const;

        static bool isOnBoard(int x,int y);
};

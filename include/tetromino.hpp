#pragma once

#include <common.hpp>
#include <screenInterface.hpp>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>  // Ensure Screen implements the required interface
class Tetromino{
    private:
        int m_x = (tetris::BOARD_WIDTH - tetris::SHAPESIZE)/2;
        int m_y = 0;
        bool m_beenHeld = false;
        bool m_isPreview = false; 
        int m_shapeIndex = tetris::randomTetrominoIndex();
        tetris::Direction m_direction = tetris::DEFAULT_SHAPE_DIRECTION; 

    public:
        Tetromino(){};
        Tetromino(int y) : m_y(y){};
        Tetromino(int x, int y, bool held) : m_x(x), m_y(y), m_beenHeld(held){};
        
        bool isFilledAt(int x, int y) const;
        void hold();
        bool hasBeenHeld() const; 
        
        void reset();
        void tick();
        void move(tetris::Direction directionToMove);
        void rotateRight();
        
        void draw(bool isPreview=false) const;
        void drawAt(int x, int y,bool isPreview=false) const;
        tetris::Color getColor() const;
        tetris::Color getPreviewColor() const;
        int getX() const;
        int getY() const;
        char getShape() const;
        
        static Tetromino<screenInterface> testMove(Tetromino<screenInterface> bl, tetris::Direction directionToMove);
        static Tetromino<screenInterface> testTick(Tetromino<screenInterface> bl);
};
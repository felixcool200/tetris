#pragma once

#include <common.hpp>

class Tetromino{
    private:
        int m_x = (tetris::BOARD_WIDTH - tetris::SHAPESIZE)/2;
        int m_y = -1;
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
        void move(tetris::Direction directionToPressed);
        void draw(bool isPreview=false) const;
        void drawAt(int x, int y,bool isPreview=false) const;
        void rotateRight();
        void update();
        
        tetris::Color getColor() const;
        tetris::Color getPreviewColor() const;
        int getX() const;
        int getY() const;
        char getShape() const;
};
Tetromino testMove(Tetromino bl, tetris::Direction directionToMove);
Tetromino testTick(Tetromino bl);

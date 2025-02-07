#pragma once

#include <common.hpp>

class Tetromino{
    private:
        int m_x = 0;
        int m_y = 0;
        bool m_beenHeld = false;
        bool m_isPreview; 
        int m_shapeIndex;
        int m_direction;

    public:
        Tetromino() : Tetromino((tetris::BOARD_WIDTH-tetris::SHAPESIZE)/2,-1,false){};
        Tetromino(int y) : Tetromino((tetris::BOARD_WIDTH-tetris::SHAPESIZE)/2,y,false){};
        Tetromino(bool held) : Tetromino((tetris::BOARD_WIDTH-tetris::SHAPESIZE)/2,-1, held){};
        Tetromino(int x, int y, bool held);
        //Tetromino(const Tetromino &o);
        
        bool isFilledAt(int x, int y) const;
        void hold();
        bool hasBeenHeld() const; 
        
        void reset();
        void tick();
        void move(tetris::Control ch);
        void draw(bool isPreview=false) const;
        void drawAt(int x, int y,bool isPreview=false);
        void rotateRight();
        void update();
        
        tetris::Color getColor() const;
        tetris::Color getPreviewColor() const;
        int getX() const;
        int getY() const;
        char getShape() const;
};
Tetromino testMove(Tetromino bl,tetris::Control ch);
Tetromino testTick(Tetromino bl);

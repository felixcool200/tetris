#pragma once
#include "constants.hpp"
class Tetromino{
    private:
        int m_x;
        int m_y;
        bool m_beenHeld;
        bool m_isPreview;
        int m_shapeIndex;
        int m_direction;
    public:
        Tetromino() : Tetromino((BOARD_WIDTH-SHAPESIZE)/2,-1,false){};
        Tetromino(int y) : Tetromino((BOARD_WIDTH-SHAPESIZE)/2,y,false){};
        Tetromino(bool held) : Tetromino((BOARD_WIDTH-SHAPESIZE)/2,-1, held){};
        Tetromino(int x, int y, bool held);
        Tetromino(const Tetromino &o);
        
        bool isFilledAt(int x, int y);
        void hold();
        bool hasBeenHeld(); 
        
        void reset();
        void tick();
        void move(int ch);
        void draw(bool isPreview=false);
        void drawAt(int x, int y,bool isPreview=false);
        void rotateRight();
        void update();
        
        int getX();
        int getY();
        int getColor();
        int getPreviewColor();
        char getShape();
};
Tetromino testMove(Tetromino bl,int ch);
Tetromino testTick(Tetromino bl);

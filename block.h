#pragma once
#include "shape.h"
#include <ncurses.h>
class Block{
    private:
        int m_x;
        int m_y;
        bool m_beenHeld;

        Shape m_shape; 
    public:
        Block() : Block((BOARD_WIDTH-SHAPESIZE)/2,-1,false){};
        Block(int y) : Block((BOARD_WIDTH-SHAPESIZE)/2,y,false){};
        Block(bool held) : Block((BOARD_WIDTH-SHAPESIZE)/2,-1, held){};
        Block(int x, int y, bool held);
        
        bool getShape(int x, int y);
        void hold();
        bool hasBeenHeld(); 
        
        void reset();
        void tick();
        void move(int ch);
        void draw(WINDOW*& screen);
        void rotateRight();
        void update();
        
        int getX();
        int getY();
        int getColor();
};
Block testMove(Block bl,int ch);
Block testTick(Block bl);
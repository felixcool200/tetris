#pragma once
#include "shape.h"
#include <ncurses.h>
class Block{
    private:
        int m_x;
        int m_y;
        bool m_fast;
        Shape m_shape; 
    public:
        Block() : Block(BOARD_WIDTH/2,0){}; // Default constructor
        Block(int x, int y);
        Block(int x, int y, Shape shape);
        void tick();
        void move(int ch);
        void draw(WINDOW*& screen);
        bool getShape(int x, int y);
        void rotateRight();
        void update();
        int getX();
        int getY();
};
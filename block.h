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
        Block(); // Default constructor
        Block(int x, int y);
        Block(int x, int y, Shape shape);
        void move(int ch);
        void draw(WINDOW*& screen);
        void rotateRight();
        void update();
        int getX();
        int getY();
};
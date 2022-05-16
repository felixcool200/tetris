#pragma once
#include "shape.h"
class Block{
    private:
        int m_x;
        int m_y;
        Shape m_shape; 
    public:
        Block(); // Default constructor
        Block(int x, int y);
        Block(int x, int y,Shape shape);
        void move(int ch);
        void rotateRight();


};
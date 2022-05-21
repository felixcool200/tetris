#pragma once
#include "constants.h"
class Shape{
    private:
        bool m_matrix[SHAPESIZE][SHAPESIZE];
        short m_direction = 0; // plus means right
    
        bool setShape(int index);
    public:
        Shape();
        Shape(int shape);
        bool getShape(int x,int y);
        void rotateRight();
        void rotateLeft();
};
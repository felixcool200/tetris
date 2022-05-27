#pragma once
#include "constants.h"
class Shape{
    private:
        const bool (*m_matrix)[SHAPESIZE] = nullptr; //Work fine
        short m_direction = 1; // plus means right
    
        void setShape(int index);
    public:
        Shape();
        Shape(int shapeIndex);
        bool getShape(int x,int y);
        void rotateRight();
        void rotateLeft();
};
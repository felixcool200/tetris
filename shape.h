#pragma once
#include "constants.h"
class Shape{
    private:
        //const bool (*m_matrix)[SHAPESIZE] = nullptr; //Works fine breaks on shallow copy
        bool m_matrix[SHAPESIZE][SHAPESIZE]; //Works fine breaks on shallow copy
        short m_direction = 1; // plus means right
        void setMatrix(const bool[SHAPESIZE][SHAPESIZE]);
        void setShape(int index);
    public:
        Shape();
        Shape(int shapeIndex);
        bool getShape(int x,int y);
        void rotateRight();
        void rotateLeft();
};
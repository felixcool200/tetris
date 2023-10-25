#pragma once
#include "constants.hpp"
class Shape{
    private:
        int m_index;
        short m_direction; // plus means right
        //const bool (*m_matrix)[SHAPESIZE] = nullptr; //Works fine breaks on shallow copy
        bool m_matrix[SHAPESIZE][SHAPESIZE]; //Works fine breaks on shallow copy
        void setMatrix(const bool[SHAPESIZE][SHAPESIZE]);
        void setShape(int index);
    public:
        Shape();
        Shape(int shapeIndex);
        bool isFilledAt(int x,int y);
        char getShape();
        void rotateRight();
        void reset();
        void rotateLeft();
        int getColor();
        int getPreviewColor();
};

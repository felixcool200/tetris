#pragma once
#include "constants.h"

class Square{
    private:
        bool m_board;
        int m_color;
        
    public:
        Square();
        void place(int color);
        void remove();

        bool isPlaced();
        void replace(Square s);
        int getColor();
};
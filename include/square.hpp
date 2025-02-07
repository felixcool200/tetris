#pragma once
#include <common.hpp>

class Square{
    private:
        bool m_filled = false;
        tetris::Color m_color = tetris::Color::NONE;
        
    public:
        void place(tetris::Color color);
        void remove();

        bool isPlaced() const;
        void replace(Square s);
        tetris::Color getColor() const;
};

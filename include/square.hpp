#pragma once
#include <common.hpp>

class Square {
   private:
    bool m_filled = false;
    tetris::Color m_color = tetris::Color::NONE;

   public:
    void place(tetris::Color color);
    void remove();

    void replace(Square s);
    bool isPlaced() const { return m_filled; };
    tetris::Color getColor() const { return m_color; };
};

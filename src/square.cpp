#include <square.hpp>

void Square::place(tetris::Color color) {
    m_filled = true;
    m_color = color;
}

void Square::remove() {
    m_filled = false;
    m_color = tetris::Color::NONE;
}

void Square::replace(const Square s) {
    m_filled = s.m_filled;
    m_color = s.m_color;
}
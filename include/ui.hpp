#pragma once

#include "tetromino.hpp"

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>  // Ensure Screen implements the required interface
class UI {
    public:
        static void drawHold(Tetromino<screenInterface> hold);
        static void drawNext(Tetromino<screenInterface> hold);
        static void drawBorders();
        static void draw(Tetromino<screenInterface> hold,Tetromino<screenInterface> next,unsigned int score,unsigned int lines,unsigned short level);
        static void drawStats(unsigned int score,unsigned int lines,unsigned short level);
};

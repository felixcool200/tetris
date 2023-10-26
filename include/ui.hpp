#pragma once
#include "tetromino.hpp"
namespace UI{
    void drawHold(Tetromino hold);
    void drawNext(Tetromino hold);
    void drawBorders();
    void draw(Tetromino hold,Tetromino next,unsigned int score,unsigned int lines,unsigned short level);
    void drawStats(unsigned int score,unsigned int lines,unsigned short level);
}

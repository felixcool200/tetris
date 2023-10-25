#pragma once
#include "constants.hpp"
#include "block.hpp"
namespace UI{
    void drawHold(Block hold);
    void drawNext(Block hold);
    void drawBorders();
    void draw(Block hold,Block next,unsigned int score,unsigned int lines,unsigned short level);
    void drawStats(unsigned int score,unsigned int lines,unsigned short level);
}

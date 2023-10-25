#pragma once
#include "constants.hpp"
#include "block.hpp"
#include <ncurses.h>
namespace UI{
    void drawHold(WINDOW*& screen, Block hold);
    void drawNext(WINDOW*& screen, Block hold);
    void drawBorders(WINDOW*& screen);
    void draw(WINDOW*& screen, Block hold,Block next,unsigned int score,unsigned int lines);
    void drawStats(WINDOW*& screen,unsigned int score,unsigned int lines);
}

#pragma once
#include "constants.h"
#include "block.h"
#include <ncurses.h>
namespace UI{
    void drawBoardBorders(WINDOW*& screen);
    void drawHold(WINDOW*& screen, Block hold);
    void drawBorder(WINDOW*& screen);
    void draw(WINDOW*& screen, Block hold);
    void update();
}
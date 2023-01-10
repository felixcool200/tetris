#pragma once
#include "constants.hpp"
#include "block.hpp"
#include <ncurses.hpp>
namespace UI{
    void drawBoardBorders(WINDOW*& screen);
    void drawHold(WINDOW*& screen, Block hold);
    void drawBorder(WINDOW*& screen);
    void draw(WINDOW*& screen, Block hold);
    void update();
}

#pragma once
#include "constants.h"
#include "block.h"
#include <ncurses.h>
class UI{
    private:
        void drawBoardBorders(WINDOW*& screen);
        void drawHold(WINDOW*& screen, Block hold);
        void drawBorder(WINDOW*& screen);
    public:
        void draw(WINDOW*& screen, Block hold);
        UI();
        void update();
};
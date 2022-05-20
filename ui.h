#pragma once
#include "constants.h"
#include <ncurses.h>
class UI{
    private:
    public:
        UI();
        void draw(WINDOW*& screen);
        void update();
};
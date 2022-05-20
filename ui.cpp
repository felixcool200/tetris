#include "ui.h"
#include <string>

    UI::UI(){

    }

    void UI::update(){
        //Should update score and nextblock.
    }
    
    void UI::draw(WINDOW*& screen){
        const char* hline = std::string(BOARD_WIDTH + 2, '#').c_str();
        wmove(screen, 0, 0);
        waddstr(screen,hline);
        wmove(screen, BOARD_HEIGHT, 0);
        waddstr(screen,hline);
        for(int i = 1; i < BOARD_HEIGHT; ++i){
            mvwaddch(screen, i, 0, '#');
            mvwaddch(screen, i, BOARD_WIDTH + 1, '#');
        }
    }
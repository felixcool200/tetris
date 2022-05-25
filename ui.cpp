#include "ui.h"
#include <string>
#include "ScreenHandler.h"

    UI::UI(){

    }

    void UI::update(){
        //Should update score and nextblock.
    }
    
    void UI::draw(WINDOW*& screen){
        std::string hline = std::string(BOARD_WIDTH + BORDER_LEFT + BORDER_RIGHT, '#');
        ScreenHandler::addStringAt(screen,hline,0,0);
        ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT);
        for(int i = 1; i < BOARD_HEIGHT; ++i){
            ScreenHandler::addCharAt(screen,'#',0,i);
            ScreenHandler::addCharAt(screen,'#',(BOARD_WIDTH + BORDER_LEFT),i);
        }
    }
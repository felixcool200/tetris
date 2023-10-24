#include "../include/ui.hpp"
#include "../include/block.hpp"
#include "../include/screenHandler.hpp"
#include <string>

void UI::update(){
    //Should update score and nextblock.
}

void UI::draw(WINDOW*& screen,Block hold){
    drawBoardBorders(screen);
    drawBorder(screen);
    drawHold(screen,hold);
}

void UI::drawBorder(WINDOW*& screen){
    std::string hline = std::string(BOARD_WIDTH + BORDER_LEFT + BORDER_RIGHT, '#');
    ScreenHandler::addStringAt(hline,0,0,screen);
    ScreenHandler::addStringAt(hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1,screen);
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',0,i,-1,screen);
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT),i,-1,screen);
    }
}

void UI::drawHold(WINDOW*& screen,Block bl){
    std::string hline = std::string(BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Hold",1,1,screen);
    ScreenHandler::addStringAt(hline,0,SHAPESIZE+3,screen);
    //ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if(bl.getY() != -2){
        //This makes the blocks look better in the holding space
        if(bl.getShape() == 'I'){
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(screen,1,2);
    }
}

void UI::drawBoardBorders(WINDOW*& screen){
    std::string hline = std::string(BOARD_WIDTH+2, '#');
    ScreenHandler::addStringAt(hline,BORDER_LEFT-1,0, screen);
    ScreenHandler::addStringAt(hline,BORDER_LEFT-1,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1, screen);
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',BORDER_LEFT - 1,i,-1,screen);
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT),i,-1,screen);
    }
}

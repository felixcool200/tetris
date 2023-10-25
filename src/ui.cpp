#include "../include/ui.hpp"
#include "../include/constants.hpp"
#include "../include/block.hpp"
#include "../include/screenHandler.hpp"
#include <string>
#include <iostream>

void UI::draw(WINDOW*& screen,Block hold,Block next,unsigned int score,unsigned int lines){
    drawBorders(screen);
    drawHold(screen,hold);
    drawNext(screen,next);
    drawStats(screen,score,lines);
}

void UI::drawStats(WINDOW*& screen,unsigned int score,unsigned int lines){

    const int offset = BOARD_WIDTH + BORDER_LEFT + 1;
    
    //Score
    ScreenHandler::addStringAt("Score: ",offset,1,screen);
    ScreenHandler::addStringAt(std::to_string(score),offset,2,screen);

    //Lines Cleared
    ScreenHandler::addStringAt("lines: ",offset,4,screen);
    ScreenHandler::addStringAt(std::to_string(lines),offset,5,screen);

    //Controls
        ScreenHandler::addStringAt("lines: ",offset,4,screen);
    ScreenHandler::addStringAt(std::to_string(lines),offset,5,screen);
}

void UI::drawBorders(WINDOW*& screen){
    //std::string hline = std::string(BOARD_WIDTH+2, '#');
    std::string hline = std::string(BOARD_WIDTH + BORDER_LEFT + BORDER_RIGHT, '#');
    
    ScreenHandler::addStringAt(hline,0,0,screen); // Top border
    ScreenHandler::addStringAt(hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1,screen); // Bottom border

    //Vertical Lines
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',0,i,-1,screen); //Left border
        ScreenHandler::addCharAt('#',BORDER_LEFT - 1,i,-1,screen); //Left Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT),i,-1,screen); // Right Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT+BORDER_RIGHT - 1),i,-1,screen); //Right border
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

void UI::drawNext(WINDOW*& screen,Block bl){
    std::string hline = std::string(BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Next",1,1+SHAPESIZE+3,screen);
    ScreenHandler::addStringAt(hline,0,2*(SHAPESIZE+3),screen);
    //ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if(bl.getY() != -2){
        //This makes the blocks look better in the holding space
        if(bl.getShape() == 'I'){
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(screen,1,2+SHAPESIZE+3);
    }
}

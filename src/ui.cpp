#include "../include/ui.hpp"
#include "../include/constants.hpp"
#include "../include/block.hpp"
#include "../include/screenHandler.hpp"
#include <string>
#include <iostream>

void UI::draw(WINDOW*& screen,Block hold,Block next,unsigned int score,unsigned int lines,unsigned short level){
    drawBorders(screen);
    drawHold(screen,hold);
    drawNext(screen,next);
    drawStats(screen,score,lines,level);
}

void UI::drawStats(WINDOW*& screen,unsigned int score,unsigned int lines,unsigned short level){

    const int offset = BOARD_WIDTH + BORDER_LEFT + 1;
    const int SCORE_OFFSET =  1;
    const int LINES_OFFSET =  3;
    const int LEVEL_OFFSET =  5;
    const int CONTROL_OFFSET = 10;

    //Score
    ScreenHandler::addStringAt("Score:",offset,SCORE_OFFSET,screen);
    ScreenHandler::addStringAt(std::to_string(score),offset,SCORE_OFFSET+1,COLOR_TEXT_CYAN,screen);

    //Lines Cleared
    ScreenHandler::addStringAt("Lines:",offset,LINES_OFFSET,screen);
    ScreenHandler::addStringAt(std::to_string(lines),offset,LINES_OFFSET+1,COLOR_TEXT_GREEN,screen);

    //Level
    ScreenHandler::addStringAt("Score:",offset,LEVEL_OFFSET,screen);
    ScreenHandler::addStringAt(std::to_string(level),offset,LEVEL_OFFSET+1,COLOR_TEXT_CYAN,screen);

    //Controls
    ScreenHandler::addStringAt("Controls",offset,CONTROL_OFFSET,COLOR_TEXT_RED,screen);

    //TODO: Fix hardcoding since the char is a whitespace
    ScreenHandler::addStringAt("Drop:\"", offset, CONTROL_OFFSET+1,screen);
    ScreenHandler::addCharAt(DROP_KEY, offset + 6,CONTROL_OFFSET+1, screen);
    ScreenHandler::addStringAt("\"", offset+7, CONTROL_OFFSET+1,screen);

    ScreenHandler::addStringAt("Preview:", offset, CONTROL_OFFSET+2,screen);
    ScreenHandler::addCharAt(TOGGLE_PREVIEW_KEY, offset + 8,CONTROL_OFFSET+2,COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Rotate:", offset, CONTROL_OFFSET+3,screen);
    ScreenHandler::addCharAt(ROTATE_BLOCK_KEY, offset + 8,CONTROL_OFFSET+3, COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Left:", offset, CONTROL_OFFSET+4,screen);
    ScreenHandler::addCharAt(MOVE_LEFT_KEY, offset + 8,CONTROL_OFFSET+4, COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Right:", offset,CONTROL_OFFSET+5,screen);
    ScreenHandler::addCharAt(MOVE_RIGHT_KEY, offset + 8,CONTROL_OFFSET+5, COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Down:", offset, CONTROL_OFFSET+6,screen);
    ScreenHandler::addCharAt(MOVE_DOWN_KEY, offset + 8,CONTROL_OFFSET+6, COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Quit:", offset, CONTROL_OFFSET+7,screen);
    ScreenHandler::addCharAt(QUIT_KEY, offset + 8,CONTROL_OFFSET+7,COLOR_TEXT_YELLOW, screen);

    ScreenHandler::addStringAt("Hold:", offset, CONTROL_OFFSET+8,screen);
    ScreenHandler::addCharAt(HOLD_KEY, offset + 8,CONTROL_OFFSET+8, COLOR_TEXT_YELLOW, screen);
}

void UI::drawBorders(WINDOW*& screen){
    //std::string hline = std::string(BOARD_WIDTH+2, '#');
    std::string hline = std::string(BOARD_WIDTH + BORDER_LEFT + BORDER_RIGHT, '#');
    
    ScreenHandler::addStringAt(hline,0,0,screen); // Top border
    ScreenHandler::addStringAt(hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1,screen); // Bottom border

    //Vertical Lines
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',0,i,screen); //Left border
        ScreenHandler::addCharAt('#',BORDER_LEFT - 1,i,screen); //Left Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT),i,screen); // Right Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT+BORDER_RIGHT - 1),i,screen); //Right border
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

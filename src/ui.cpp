#include "../include/ui.hpp"
#include "../include/constants.hpp"
#include "../include/tetromino.hpp"
#include "../include/screenHandler.hpp"
#include <string>
#include <iostream>

void UI::draw(Tetromino hold,Tetromino next,unsigned int score,unsigned int lines,unsigned short level){
    drawBorders();
    drawHold(hold);
    drawNext(next);
    drawStats(score,lines,level);
}

void UI::drawStats(unsigned int score,unsigned int lines,unsigned short level){

    const int offset = BOARD_WIDTH + BORDER_LEFT + 1;
    const int SCORE_OFFSET =  1;
    const int LINES_OFFSET =  3;
    const int LEVEL_OFFSET =  5;
    const int CONTROL_OFFSET = 10;

    //Score
    ScreenHandler::addStringAt("Score:",offset,SCORE_OFFSET);
    ScreenHandler::addStringAt(std::to_string(score),offset,SCORE_OFFSET+1,COLOR_TEXT_CYAN);

    //Lines Cleared
    ScreenHandler::addStringAt("Lines:",offset,LINES_OFFSET);
    ScreenHandler::addStringAt(std::to_string(lines),offset,LINES_OFFSET+1,COLOR_TEXT_GREEN);

    //Level
    ScreenHandler::addStringAt("Level:",offset,LEVEL_OFFSET);
    ScreenHandler::addStringAt(std::to_string(level),offset,LEVEL_OFFSET+1,COLOR_TEXT_CYAN);

    //Controls
    ScreenHandler::addStringAt("Controls",offset,CONTROL_OFFSET,COLOR_TEXT_RED);

    ScreenHandler::addStringAt("Drop:\"", offset, CONTROL_OFFSET+1);
    ScreenHandler::addCharAt(DROP_KEY, offset + 6,CONTROL_OFFSET+1);
    ScreenHandler::addStringAt("\"", offset+7, CONTROL_OFFSET+1);

    const int length = 7;
    const std::string key_names[length] = {"Preview:","Rotate:","Left:","Right:","Down:","Quit:","Hold"};
    const char keys[length] = {TOGGLE_PREVIEW_KEY,ROTATE_TETROMINO_KEY,MOVE_LEFT_KEY,MOVE_RIGHT_KEY,MOVE_DOWN_KEY,QUIT_KEY,HOLD_KEY};

    for(int i=0; i < length;++i){
        ScreenHandler::addStringAt(key_names[i], offset, CONTROL_OFFSET+2+i);
        ScreenHandler::addCharAt(keys[i], offset + 8,CONTROL_OFFSET+2+i,COLOR_TEXT_YELLOW);
    }
}

void UI::drawBorders(){
    //std::string hline = std::string(BOARD_WIDTH+2, '#');
    std::string hline = std::string(BOARD_WIDTH + BORDER_LEFT + BORDER_RIGHT, '#');
    
    ScreenHandler::addStringAt(hline,0,0); // Top border
    ScreenHandler::addStringAt(hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1); // Bottom border

    //Vertical Lines
    for(int i = 1; i < BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',0,i); //Left border
        ScreenHandler::addCharAt('#',BORDER_LEFT - 1,i); //Left Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT),i); // Right Game border
        ScreenHandler::addCharAt('#',(BOARD_WIDTH + BORDER_LEFT+BORDER_RIGHT - 1),i); //Right border
    }
}

void UI::drawHold(Tetromino bl){
    std::string hline = std::string(BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Hold",1,1);
    ScreenHandler::addStringAt(hline,0,SHAPESIZE+3);
    //ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if(bl.getY() != -2){
        //This makes the blocks look better in the holding space
        if(bl.getShape() == 'I'){
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(1,2);
    }
}

void UI::drawNext(Tetromino bl){
    std::string hline = std::string(BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Next",1,1+SHAPESIZE+3);
    ScreenHandler::addStringAt(hline,0,2*(SHAPESIZE+3));
    //ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if(bl.getY() != -2){
        //This makes the blocks look better in the holding space
        if(bl.getShape() == 'I'){
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(1,2+SHAPESIZE+3);
    }
}

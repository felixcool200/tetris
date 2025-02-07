#include <string>
#include <iostream>
#include <utility>
#include <string_view>
#include <ranges>

#include <ui.hpp>
#include <common.hpp>
#include <tetromino.hpp>
#include <screenHandler.hpp>

void UI::draw(Tetromino hold,Tetromino next,unsigned int score,unsigned int lines,unsigned short level){
    drawBorders();
    drawHold(hold);
    drawNext(next);
    drawStats(score,lines,level);
}

void UI::drawStats(unsigned int score,unsigned int lines,unsigned short level){

    using namespace std::string_view_literals;
    constexpr int offset = tetris::BOARD_WIDTH + tetris::BORDER_LEFT + 1;
    constexpr int SCORE_OFFSET =  1;
    constexpr int LINES_OFFSET =  3;
    constexpr int LEVEL_OFFSET =  5;
    constexpr int CONTROL_OFFSET = 10;

    //Score
    ScreenHandler::addStringAt("Score:"sv,offset,SCORE_OFFSET);
    ScreenHandler::addStringAt(std::to_string(score),offset,SCORE_OFFSET+1,tetris::Color::TEXT_CYAN);

    //Lines Cleared
    ScreenHandler::addStringAt("Lines:"sv,offset,LINES_OFFSET);
    ScreenHandler::addStringAt(std::to_string(lines),offset,LINES_OFFSET+1,tetris::Color::TEXT_GREEN);

    //Level
    ScreenHandler::addStringAt("Level:"sv,offset,LEVEL_OFFSET);
    ScreenHandler::addStringAt(std::to_string(level),offset,LEVEL_OFFSET+1,tetris::Color::TEXT_CYAN);

    //Control
    ScreenHandler::addStringAt("Control"sv,offset,CONTROL_OFFSET,tetris::Color::TEXT_RED);

    ScreenHandler::addStringAt("Drop:\""sv, offset, CONTROL_OFFSET+1);
    ScreenHandler::addCharAt(tetris::ControlTools::enumToValue(tetris::Control::DROP_KEY), offset + 6,CONTROL_OFFSET+1);
    ScreenHandler::addStringAt("\"", offset+7, CONTROL_OFFSET+1);

    std::array<std::pair<std::string_view,tetris::Control>,tetris::TETROMINOS> controls= 
    {{
        {"Preview:"sv, tetris::Control::TOGGLE_PREVIEW_KEY},
        {"Rotate:"sv,  tetris::Control::ROTATE_TETROMINO_KEY},
        {"Left:"sv,    tetris::Control::MOVE_LEFT_KEY},
        {"Right:"sv,   tetris::Control::MOVE_RIGHT_KEY},
        {"Down:"sv,    tetris::Control::MOVE_DOWN_KEY},
        {"Quit:"sv,    tetris::Control::QUIT_KEY},
        {"Hold"sv,     tetris::Control::HOLD_KEY},

    }};

    for (auto const [index, control] : std::views::enumerate(controls)){
        ScreenHandler::addStringAt(control.first, offset, CONTROL_OFFSET+2+index);
        ScreenHandler::addCharAt(tetris::ControlTools::enumToValue(control.second), offset + 8,CONTROL_OFFSET+2+index, tetris::Color::TEXT_YELLOW);
    }
}

void UI::drawBorders(){
    //std::string hline = std::string(BOARD_WIDTH+2, '#');
    std::string hline = std::string(tetris::BOARD_WIDTH + tetris::BORDER_LEFT + tetris::BORDER_RIGHT, '#');
    
    ScreenHandler::addStringAt(hline,0,0); // Top border
    ScreenHandler::addStringAt(hline,0,tetris::BOARD_HEIGHT + tetris::BORDER_TOP + tetris::BORDER_BOTTOM - 1); // Bottom border

    //Vertical Lines
    for(int i = 1; i < tetris::BOARD_HEIGHT + 1; ++i){
        ScreenHandler::addCharAt('#',0,i); //Left border
        ScreenHandler::addCharAt('#', tetris::BORDER_LEFT - 1, i); //Left Game border
        ScreenHandler::addCharAt('#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT),i); // Right Game border
        ScreenHandler::addCharAt('#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT+tetris::BORDER_RIGHT - 1),i); //Right border
    }
}

void UI::drawHold(Tetromino bl){
    std::string hline = std::string(tetris::BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Hold",1,1);
    ScreenHandler::addStringAt(hline,0,tetris::SHAPESIZE+3);
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
    std::string hline = std::string(tetris::BORDER_LEFT, '#');
    ScreenHandler::addStringAt("Next",1,1+tetris::SHAPESIZE+3);
    ScreenHandler::addStringAt(hline,0,2*(tetris::SHAPESIZE+3));
    //ScreenHandler::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if(bl.getY() != -2){
        //This makes the blocks look better in the holding space
        if(bl.getShape() == 'I'){
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(1,2+tetris::SHAPESIZE+3);
    }
}

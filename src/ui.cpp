#include <ui.hpp>
#include <common.hpp>
#include <screenInterface.hpp>

#include <string>
#include <iostream>
#include <utility>
#include <string_view>
#include <ranges>

#include <ScreenToUse.hpp>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::draw(Tetromino<screenInterface> hold,Tetromino<screenInterface> next,unsigned int score,unsigned int lines, unsigned int level) {
    drawBorders();
    drawHold(hold);
    drawNext(next);
    drawStats(score, lines, level);
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawStats(unsigned int score, unsigned int lines, unsigned int level) {

    using namespace std::string_view_literals;
    constexpr size_t offset = tetris::BOARD_WIDTH + tetris::BORDER_LEFT + 1;
    constexpr size_t SCORE_OFFSET =  1;
    constexpr size_t LINES_OFFSET =  3;
    constexpr size_t LEVEL_OFFSET =  5;
    constexpr size_t CONTROL_OFFSET = 10;

    //Score
    screenInterface::addStringAt("Score:"sv,offset,SCORE_OFFSET);
    screenInterface::addStringAt(std::to_string(score),offset,SCORE_OFFSET+1,tetris::Color::TEXT_CYAN);

    //Lines Cleared
    screenInterface::addStringAt("Lines:"sv,offset,LINES_OFFSET);
    screenInterface::addStringAt(std::to_string(lines),offset,LINES_OFFSET+1,tetris::Color::TEXT_GREEN);

    //Level
    screenInterface::addStringAt("Level:"sv,offset,LEVEL_OFFSET);
    screenInterface::addStringAt(std::to_string(level),offset,LEVEL_OFFSET+1,tetris::Color::TEXT_CYAN);

    //Control
    screenInterface::addStringAt("Control"sv,offset,CONTROL_OFFSET,tetris::Color::TEXT_RED);

    screenInterface::addStringAt("Drop:\""sv, offset, CONTROL_OFFSET+1);
    screenInterface::addCharAt(tetris::ControlTools::enumToValue(tetris::Control::DROP_KEY), offset + 6,CONTROL_OFFSET+1);
    screenInterface::addStringAt("\"", offset+7, CONTROL_OFFSET+1);

    std::array<std::pair<std::string_view, tetris::Control>, 8> controls = 
    {{
        {"Preview:"sv, tetris::Control::TOGGLE_PREVIEW_KEY},
        {"Rotate:"sv,  tetris::Control::ROTATE_TETROMINO_KEY},
        {"Left:"sv,    tetris::Control::MOVE_LEFT_KEY},
        {"Right:"sv,   tetris::Control::MOVE_RIGHT_KEY},
        {"Down:"sv,    tetris::Control::MOVE_DOWN_KEY},
        {"Quit:"sv,    tetris::Control::QUIT_KEY},
        {"Hold"sv,     tetris::Control::HOLD_KEY},
        {"Pause"sv,    tetris::Control::PAUSE_KEY},
    }};

    for (auto const [index, control] : std::views::enumerate(controls)) {
        const auto yOffset = static_cast<int>(CONTROL_OFFSET+2+index);
        screenInterface::addStringAt(control.first, offset, yOffset);
        screenInterface::addCharAt(tetris::ControlTools::enumToValue(control.second), offset + 8, yOffset, tetris::Color::TEXT_YELLOW);
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawBorders() {
    //std::string hline = std::string(BOARD_WIDTH+2, '#');
    std::string hline = std::string(tetris::BOARD_WIDTH + tetris::BORDER_LEFT + tetris::BORDER_RIGHT, '#');
    
    screenInterface::addStringAt(hline,0,0); // Top border
    screenInterface::addStringAt(hline,0,tetris::BOARD_HEIGHT + tetris::BORDER_TOP + tetris::BORDER_BOTTOM - 1); // Bottom border

    //Vertical Lines
    for(int i = 1; i < tetris::BOARD_HEIGHT + 1; ++i) {
        screenInterface::addCharAt('#',0,i); //Left border
        screenInterface::addCharAt('#', tetris::BORDER_LEFT - 1, i); //Left Game border
        screenInterface::addCharAt('#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT),i); // Right Game border
        screenInterface::addCharAt('#', (tetris::BOARD_WIDTH + tetris::BORDER_LEFT+tetris::BORDER_RIGHT - 1),i); //Right border
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawHold(Tetromino<screenInterface> bl) {
    std::string hline = std::string(tetris::BORDER_LEFT, '#');
    screenInterface::addStringAt("Hold",1,1);
    screenInterface::addStringAt(hline,0,tetris::SHAPESIZE+3);
    //screenInterface::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if (bl.getY() != -2) {
        //This makes the blocks look better in the holding space
        if (bl.getShape() == 'I') {
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(1,2);
    }
}

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>
void UI<screenInterface>::drawNext(Tetromino<screenInterface> bl) {
    std::string hline = std::string(tetris::BORDER_LEFT, '#');
    screenInterface::addStringAt("Next",1,1+tetris::SHAPESIZE+3);
    screenInterface::addStringAt(hline,0,2*(tetris::SHAPESIZE+3));
    //screenInterface::addStringAt(screen,hline,0,BOARD_HEIGHT + BORDER_TOP + BORDER_BOTTOM - 1);
    if (bl.getY() != -2) {
        //This makes the blocks look better in the holding space
        if (bl.getShape() == 'I') {
            bl.rotateRight();
        }
        bl.rotateRight();
        bl.drawAt(1,2+tetris::SHAPESIZE+3);
    }
}

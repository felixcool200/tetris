#include <ncursesScreen.hpp>

#include <common.hpp>
#include <game.hpp>

#include <ncurses.h>

#include <iostream>
#include <string_view>
#include <string>
#include <stdexcept>

namespace {
    enum class NcurseColor {
        // Empty value
        NONE,
        BLACK,
        RED,
        GREEN,
        YELLOW,
        BLUE,
        MAGENTA,
        CYAN,
        WHITE,
    
        //User defined colors
        PREVIEW_YELLOW,
        PREVIEW_CYAN,
        PREVIEW_GREEN,
        PREVIEW_RED,
        PREVIEW_WHITE,
        PREVIEW_BLUE,
        PREVIEW_MAGENTA,
    };
    
    namespace NcurseColorTools {
        constexpr std::array<std::pair<short, NcurseColor>, 16> colorMappings = {{
            {-1, NcurseColor::NONE},
            {0,  NcurseColor::BLACK},
            {1,  NcurseColor::RED},
            {2,  NcurseColor::GREEN},
            {3,  NcurseColor::YELLOW},
            {4,  NcurseColor::BLUE},
            {5,  NcurseColor::MAGENTA},
            {6,  NcurseColor::CYAN},
            {7,  NcurseColor::WHITE},
            {8,  NcurseColor::PREVIEW_YELLOW},
            {9,  NcurseColor::PREVIEW_CYAN},
            {10, NcurseColor::PREVIEW_GREEN},
            {11, NcurseColor::PREVIEW_RED},
            {12, NcurseColor::PREVIEW_WHITE},
            {13, NcurseColor::PREVIEW_BLUE},
            {14, NcurseColor::PREVIEW_MAGENTA},
        }};
    
        // Short-to-Enum conversion
        constexpr NcurseColor valueToEnum(short toFind) {
            for (const auto& [key, element] : colorMappings) {
                if (key == toFind)
                    return element;
            }
            return NcurseColor::NONE;
            //throw std::invalid_argument("Invalid input to converter");
        }
    
        // Enum-to-Short conversion
        constexpr short enumToValue(NcurseColor toFind) {
            for (const auto& [key, element] : colorMappings) {
                if (element == toFind)
                    return key;
            }
            throw std::invalid_argument("Invalid input to converter");
        }
        
    } // namespace NcurseColorTools

    void initColors(){
        //Block Colors
        using namespace tetris;
        // Initilize new colors
        const short FACTOR = 500;
    
        const std::vector<std::tuple<NcurseColor, short, short, short>> newColors = {
            {NcurseColor::PREVIEW_RED     ,FACTOR, 0,      0},
            {NcurseColor::PREVIEW_GREEN   ,0,      FACTOR, 0},
            {NcurseColor::PREVIEW_YELLOW  ,FACTOR, FACTOR, 0},
            {NcurseColor::PREVIEW_BLUE    ,0,      0,      FACTOR},
            {NcurseColor::PREVIEW_MAGENTA ,FACTOR, 0,      FACTOR},
            {NcurseColor::PREVIEW_CYAN    ,0,      FACTOR, FACTOR},
            {NcurseColor::PREVIEW_WHITE   ,FACTOR, FACTOR, FACTOR},
        };
    
        const std::vector<std::tuple<Color, NcurseColor, NcurseColor>> colors = {
            //TETROMINO Colors
            {Color::TETROMINO_BLACK,   NcurseColor::BLACK,	 NcurseColor::BLACK},
            {Color::TETROMINO_RED, 	   NcurseColor::RED,	 NcurseColor::RED},
            {Color::TETROMINO_GREEN,   NcurseColor::GREEN,	 NcurseColor::GREEN},
            {Color::TETROMINO_YELLOW,  NcurseColor::YELLOW,	 NcurseColor::YELLOW},
            {Color::TETROMINO_BLUE,    NcurseColor::BLUE,	 NcurseColor::BLUE},
            {Color::TETROMINO_MAGENTA, NcurseColor::MAGENTA, NcurseColor::MAGENTA},
            {Color::TETROMINO_CYAN,    NcurseColor::CYAN,	 NcurseColor::CYAN},
            {Color::TETROMINO_WHITE,   NcurseColor::WHITE,	 NcurseColor::WHITE},
    
            //TEXT Colors
            {Color::TEXT_BLACK,	  NcurseColor::BLACK,   NcurseColor::BLACK},
            {Color::TEXT_RED,	  NcurseColor::RED,     NcurseColor::BLACK},
            {Color::TEXT_GREEN,	  NcurseColor::GREEN,   NcurseColor::BLACK},
            {Color::TEXT_YELLOW,  NcurseColor::YELLOW,  NcurseColor::BLACK},
            {Color::TEXT_BLUE,    NcurseColor::BLUE,    NcurseColor::BLACK},
            {Color::TEXT_MAGENTA, NcurseColor::MAGENTA, NcurseColor::BLACK},
            {Color::TEXT_CYAN,	  NcurseColor::CYAN,    NcurseColor::BLACK},
            {Color::TEXT_WHITE,	  NcurseColor::WHITE,   NcurseColor::BLACK},
    
            //TETROMINO Preview Colors
            {Color::PREVIEW_RED, 	 NcurseColor::PREVIEW_RED, 	   NcurseColor::PREVIEW_RED},
            {Color::PREVIEW_GREEN,   NcurseColor::PREVIEW_GREEN,   NcurseColor::PREVIEW_GREEN},
            {Color::PREVIEW_YELLOW,  NcurseColor::PREVIEW_YELLOW,  NcurseColor::PREVIEW_YELLOW},
            {Color::PREVIEW_BLUE,    NcurseColor::PREVIEW_BLUE,    NcurseColor::PREVIEW_BLUE},
            {Color::PREVIEW_MAGENTA, NcurseColor::PREVIEW_MAGENTA, NcurseColor::PREVIEW_MAGENTA},
            {Color::PREVIEW_CYAN,    NcurseColor::PREVIEW_CYAN,    NcurseColor::PREVIEW_CYAN},
            {Color::PREVIEW_WHITE,   NcurseColor::PREVIEW_WHITE,   NcurseColor::PREVIEW_WHITE},
        };
    
        for(const auto& color: newColors){
            init_color(
                NcurseColorTools::enumToValue(static_cast<NcurseColor>(std::get<0>(color))), 
                static_cast<short>(std::get<1>(color)), // R
                static_cast<short>(std::get<2>(color)), // G
                static_cast<short>(std::get<3>(color))  // B
            );
        }
    
        for(const auto& color: colors){
            init_pair(
                ColorTools::enumToValue(static_cast<Color>(std::get<0>(color))), 
                NcurseColorTools::enumToValue(static_cast<NcurseColor>(std::get<1>(color))),
                NcurseColorTools::enumToValue(static_cast<NcurseColor>(std::get<2>(color)))
            );
        }
    }

    WINDOW* backBuffer = nullptr;
    
} // end namespace

Screen::StatusCode NcursesScreen::initScreen() {
    initscr(); // Create the screen
    timeout(-1); // Do not wait for input
    noecho(); // Dont echo key pressed
    keypad(stdscr, TRUE); //enable "special" characters
    curs_set(0);
    start_color();
    initColors();

    nodelay(stdscr, TRUE); // Read inputs all the time.

    int height = 0;
    int width = 0;
    getmaxyx(stdscr, height, width);
    if (height < tetris::BOARD_HEIGHT + tetris::UI_HEIGHT + 2 ||
        width < tetris::BOARD_WIDTH + tetris::UI_WIDTH + 2) {
        endwin();
        std::cerr << "Terminal too small: Height " << height << ", Width " << width << std::endl;
        return Screen::StatusCode::ERROR;
    }

    if (!has_colors()) {
        endwin();
        std::cerr << "Terminal doesn't support color\n";
        return Screen::StatusCode::ERROR;
    }

    backBuffer = newwin(height, width, 0, 0);
    if (!backBuffer) {
        endwin();
        std::cerr << "Failed to create back buffer\n";
        return Screen::StatusCode::ERROR;
    }
    keypad(backBuffer, TRUE);
    wbkgd(backBuffer, COLOR_PAIR(0));
    return Screen::StatusCode::OKEY;
}

tetris::Control NcursesScreen::getInput() {
    const auto key = getch();
    if(key == ERR) {
        return tetris::Control::NONE;
    }
    switch (key) {
        case KEY_UP:
            return tetris::Control::ROTATE;

        case KEY_DOWN:
            return tetris::Control::DOWN;

        case KEY_LEFT:
            return tetris::Control::LEFT;

        case KEY_RIGHT:
            return tetris::Control::RIGHT;
    }

    return tetris::ControlTools::valueToEnum(static_cast<char>(key));
}

Screen::StatusCode NcursesScreen::closeScreen() {
    if (backBuffer) {
        delwin(backBuffer);
        backBuffer = nullptr;
    }
    return endwin() == ERR ? Screen::StatusCode::ERROR : Screen::StatusCode::OKEY;
}

Screen::StatusCode NcursesScreen::clearScreen() {
    werase(backBuffer);
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode NcursesScreen::redrawScreen() {
    if(refresh() == ERR) {
        return Screen::StatusCode::ERROR;
    }
    wnoutrefresh(backBuffer);
    doupdate();
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode NcursesScreen::addCharAt(char ch, int x, int y, tetris::Color color) {
    const bool useColor = (has_colors() == TRUE && color != tetris::Color::NONE);

    if (useColor) {
        wattron(backBuffer, COLOR_PAIR(tetris::ColorTools::enumToValue(color)));
    }

    if (mvwaddch(backBuffer, y, x, ch) == ERR) {
        return Screen::StatusCode::ERROR;
    }
    
    if (useColor) {
        wattroff(backBuffer, COLOR_PAIR(tetris::ColorTools::enumToValue(color)));
    }

    return Screen::StatusCode::OKEY;
}

Screen::StatusCode NcursesScreen::addStringAt(std::string_view s, int x, int y, tetris::Color color) {
    for (size_t i = 0; i < s.size(); ++i) {
        if (addCharAt(s[i], x + static_cast<int>(i), y, color) != Screen::StatusCode::OKEY) {
            return Screen::StatusCode::ERROR;
        }
    }
    return Screen::StatusCode::OKEY;
}

Screen::StatusCode NcursesScreen::addCharAtBoard(char ch, int x, int y, tetris::Color color) {
    if (Game<NcursesScreen>::isOnBoard(x, y)) {
        return addCharAt(ch, x + tetris::BORDER_LEFT, y + tetris::BORDER_TOP, color);
    }
    return Screen::StatusCode::ERROR;
}

Screen::StatusCode NcursesScreen::addStringAtBoard(std::string_view s, int x, int y, tetris::Color color) {
    if (Game<NcursesScreen>::isOnBoard(x, y)){
        return addStringAt(s, x + tetris::BORDER_LEFT, y + tetris::BORDER_TOP, color);
    }
    return Screen::StatusCode::ERROR;
}
#pragma once
#include <ncurses.h>

#include <string_view>

#include "common.hpp"
#include "screenInterface.hpp"

// Implementation of the ScreenInterface for Ncurses
namespace Screen {
class NcursesScreen {
   public:
    static Screen::StatusCode initScreen();
    static Screen::StatusCode closeScreen();

    static tetris::Control getInput();

    static Screen::StatusCode clearScreen();
    static Screen::StatusCode redrawScreen();

    // Chars
    static Screen::StatusCode addCharAtBoard(char ch, size_t x, size_t y,
                                             tetris::Color color = tetris::Color::NONE);
    static Screen::StatusCode addCharAt(char ch, size_t x, size_t y,
                                        tetris::Color color = tetris::Color::NONE);

    // Strings
    static Screen::StatusCode addStringAt(std::string_view s, size_t x, size_t y,
                                          tetris::Color color = tetris::Color::NONE);
    static Screen::StatusCode addStringAtBoard(std::string_view s, size_t x, size_t y,
                                               tetris::Color color = tetris::Color::NONE);
};
}  // namespace Screen
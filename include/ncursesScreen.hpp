#pragma once
#include <ncurses.h>

#include <common.hpp>
#include <screenInterface.hpp>
#include <string>
#include <string_view>

// Implementation of the ScreenInterface for Ncurses
class NcursesScreen {
   public:
    static Screen::StatusCode initScreen();
    static Screen::StatusCode closeScreen();

    static tetris::Control getInput();

    static Screen::StatusCode clearScreen();
    static Screen::StatusCode redrawScreen();

    // Chars
    static Screen::StatusCode addCharAtBoard(char ch, int x, int y,
                                             tetris::Color color = tetris::Color::NONE);
    static Screen::StatusCode addCharAt(char ch, int x, int y,
                                        tetris::Color color = tetris::Color::NONE);

    // Strings
    static Screen::StatusCode addStringAt(std::string_view s, int x, int y,
                                          tetris::Color color = tetris::Color::NONE);
    static Screen::StatusCode addStringAtBoard(std::string_view s, int x, int y,
                                               tetris::Color color = tetris::Color::NONE);
};
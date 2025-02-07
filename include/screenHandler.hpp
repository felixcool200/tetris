#pragma once
#include <string>
#include <string_view>

#include <common.hpp>

#include <ncurses.h>

namespace ScreenHandler{
    //void moveCurserBoard(int x, int y, WINDOW*& screen=stdscr);
    
    //Chars
    /*
    void addChar(char c);
    */
    //void addCharAt(char ch, int x, int y,WINDOW*& screen=stdscr);
    void addCharAt(char ch, int x, int y, tetris::Color color=tetris::Color::NONE,WINDOW*& screen=stdscr);
    void addCharAtBoard(char ch, int x, int y, tetris::Color color=tetris::Color::NONE,WINDOW*& screen=stdscr);

    //Strings
    void addStringAt(std::string_view s, int x, int y, tetris::Color color=tetris::Color::NONE, WINDOW*& screen=stdscr);
    void addStringAtBoard(std::string_view s, int x, int y, tetris::Color color=tetris::Color::NONE, WINDOW*& screen=stdscr);
}
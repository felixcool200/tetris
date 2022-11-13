#pragma once
#include <ncurses.h>
#include <string>
namespace ScreenHandler{
    void moveCurserBoard(int x, int y, WINDOW*& screen=stdscr);
    void addChar(char c);
    void addCharAt(char ch, int x, int y, int color = -1, WINDOW*& screen=stdscr);
    void addCharAtBoard(char ch, int x, int y, int color = -1,WINDOW*& screen=stdscr);
    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen=stdscr);
    void addStringAt(std::string s, int x, int y, WINDOW*& screen=stdscr);
}

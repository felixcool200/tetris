#pragma once
#include <ncurses.h>
#include <string>
namespace ScreenHandler{
    void moveCurserBoard(WINDOW*& screen, int x, int y);
    void addChar(WINDOW*& screen, char c);
    void addCharAt(WINDOW*& screen,char ch, int x, int y);
    void addCharAtBoard(WINDOW*& screen,char ch, int x, int y);
    void addStringAt(WINDOW*& screen, std::string s, int x, int y);
}

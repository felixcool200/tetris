#pragma once
#include <ncurses.h>
#include <string>
namespace ScreenHandler{
    void moveCurserBoard(int x, int y, WINDOW*& screen=stdscr);
    
    //Chars
    void addChar(char c);
    void addCharAt(char ch, int x, int y,WINDOW*& screen=stdscr);
    void addColoredCharAt(char ch, int x, int y, int color,WINDOW*& screen=stdscr);
    void addCharAtBoard(char ch, int x, int y, WINDOW*& screen=stdscr);
    void addColoredCharAtBoard(char ch, int x, int y,int color,WINDOW*& screen=stdscr);

    //Strings
    void addStringAt(std::string s, int x, int y, WINDOW*& screen=stdscr);
    void addColoredStringAt(std::string s, int x, int y, int color, WINDOW*& screen=stdscr);
    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen=stdscr);
    void addColoredStringAtBoard(char ch, int x, int y, int color,WINDOW*& screen=stdscr);
}
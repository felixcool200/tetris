#include "../include/screenHandler.hpp"
#include "../include/constants.hpp"
#include "../include/board.hpp"
#include <ncurses.h>
#include <string>

namespace ScreenHandler{

    void moveCurserBoard(int x, int y, WINDOW*& screen){
        wmove(screen,(y + BORDER_TOP),(x + BORDER_LEFT));
    }

    void addChar(char c, WINDOW*& screen){
        waddch(screen,c);
    }
    
    void addCharAt(char ch, int x, int y, WINDOW*& screen){
        mvwaddch(screen, y, x, ch);
    }

    void addColoredCharAt(char ch, int x, int y, int color,WINDOW*& screen){
        attron(COLOR_PAIR(color));
        mvwaddch(screen, y, x, ch);
        attroff(COLOR_PAIR(color));
    }

    void addCharAtBoard(char ch, int x, int y, WINDOW*& screen){
        if(Board::isOnBoard(x,y)){
            addCharAt(ch, (x + BORDER_LEFT),(y+ BORDER_TOP), screen);
        }
    }

    void addColoredCharAtBoard(char ch, int x, int y, int color, WINDOW*& screen){
        if(Board::isOnBoard(x,y)){
            attron(COLOR_PAIR(color));
            addColoredCharAt(ch, (x + BORDER_LEFT),(y+ BORDER_TOP), color, screen);
            attroff(COLOR_PAIR(color));
        }
    }
      
    void addStringAt(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, y, x, s.c_str());
    }
          
    void addColoredStringAt(std::string s, int x, int y,int color, WINDOW*& screen){
        attron(COLOR_PAIR(color));
        mvwaddstr(screen, y, x, s.c_str());
        attroff(COLOR_PAIR(color));
    }

    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
    }
          
    void addColoredStringAtBoard(std::string s, int x, int y,int color, WINDOW*& screen){
        attron(COLOR_PAIR(color));
        mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
        attroff(COLOR_PAIR(color));
    }

}

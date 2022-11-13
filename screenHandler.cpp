#include "ScreenHandler.h"
#include "constants.h"
#include "board.h"
#include <ncurses.h>
#include <string>

namespace ScreenHandler{

    void moveCurserBoard(int x, int y, WINDOW*& screen){
        wmove(screen,(y + BORDER_TOP),(x + BORDER_LEFT));
    }

    void addChar(char c, WINDOW*& screen){
        waddch(screen,c);
    }
    
    void addCharAt(char ch, int x, int y, int color, WINDOW*& screen){
        if(color == -1){
            mvwaddch(screen, y, x, ch);
        }else{
            attron(COLOR_PAIR(color));
            mvwaddch(screen, y, x, ch);
            attroff(COLOR_PAIR(color));
        }
    }

    void addCharAtBoard(char ch, int x, int y, int color, WINDOW*& screen){
        if(Board::isOnBoard(x,y)){
            addCharAt(ch, (x + BORDER_LEFT),(y+ BORDER_TOP), color, screen);
        }
    }

    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
    }

    
    void addStringAt(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, y, x, s.c_str());
    }
}
#include "ScreenHandler.h"
#include "constants.h"
#include "board.h"
#include <ncurses.h>
#include <string>

namespace ScreenHandler{

    void moveCurserBoard(WINDOW*& screen, int x, int y){
        wmove(screen,(y + BORDER_TOP),(x + BORDER_LEFT));
        return;
    }

    void addChar(WINDOW*& screen, char c){
        waddch(screen,c);
    }
    
    void addCharAt(WINDOW*& screen,char ch, int x, int y){
        mvwaddch(screen, y, x, ch);
    }

    void addCharAtBoard(WINDOW*& screen,char ch, int x, int y, int color){
        if(Board::isOnBoard(x,y)){
            attron(COLOR_PAIR(color));
            mvwaddch(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), ch);
            attroff(COLOR_PAIR(color));
        }
    }

    void addStringAtBoard(WINDOW*& screen,std::string s, int x, int y){
        mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
    }

    
    void addStringAt(WINDOW*& screen, std::string s, int x, int y){
        mvwaddstr(screen, y, x, s.c_str());
    }
}
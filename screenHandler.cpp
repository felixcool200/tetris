#include "ScreenHandler.h"
#include "constants.h"
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

    void addCharAtBoard(WINDOW*& screen,char ch, int x, int y){
        mvwaddch(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), ch);
    }
    
    void addStringAt(WINDOW*& screen, std::string s, int x, int y){
        mvwaddstr(screen, y, x, s.c_str());
    }
}
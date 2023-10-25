#include "../include/screenHandler.hpp"
#include "../include/constants.hpp"
#include "../include/board.hpp"
#include <ncurses.h>
#include <string>

namespace ScreenHandler{

    /*
    void moveCurserBoard(int x, int y, WINDOW*& screen){
        wmove(screen,(y + BORDER_TOP),(x + BORDER_LEFT));
    }

    void addChar(char c, WINDOW*& screen){
        waddch(screen,c);
    }
    
    void addCharAt(char ch, int x, int y, WINDOW*& screen){
        mvwaddch(screen, y, x, ch);
    }

    void addCharAtBoard(char ch, int x, int y, WINDOW*& screen){
        if(Board::isOnBoard(x,y)){
            mvwaddch(screen, (x + BORDER_LEFT),(y+ BORDER_TOP), ch);
        }
    }
    */

    void addCharAt(char ch, int x, int y, int color, WINDOW*& screen){
        if (has_colors() == TRUE && color != -1) {
            attron(COLOR_PAIR(color));
            mvwaddch(screen, y, x, ch);
            attroff(COLOR_PAIR(color));
        }else{
            mvwaddch(screen, y, x, ch);
        }      
    }
    void addCharAt(char ch, int x, int y, WINDOW*& screen){
        addCharAt(ch,x,y,-1,screen);
    }

    void addCharAtBoard(char ch, int x, int y, int color, WINDOW*& screen){
        if(Board::isOnBoard(x,y)){
            if (has_colors() == TRUE && color != -1) {
                attron(COLOR_PAIR(color));
                addCharAt(ch, (x + BORDER_LEFT),(y+ BORDER_TOP), color, screen);
                attroff(COLOR_PAIR(color));
            }else{
                addCharAt(ch, (x + BORDER_LEFT),(y+ BORDER_TOP),color, screen);
            }
        }
    }
    void addCharAtBoard(char ch, int x, int y, WINDOW*& screen){
        addCharAtBoard(ch,x,y,-1,screen);
    }

    /*
    void addStringAt(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, y, x, s.c_str());
    }


    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen){
        mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
    }
    */
          
    void addStringAt(std::string s, int x, int y,int color, WINDOW*& screen){
        if (has_colors() == TRUE && color != -1) {
            attron(COLOR_PAIR(color));
            mvwaddstr(screen, y, x, s.c_str());
            attroff(COLOR_PAIR(color));
        }else{
            mvwaddstr(screen, y, x, s.c_str());
        }
    }
    
    void addStringAt(std::string s, int x, int y, WINDOW*& screen){
        addStringAt(s,x,y,-1,screen);
    }

          
    void addStringAtBoard(std::string s, int x, int y,int color, WINDOW*& screen){
        if (has_colors() == TRUE && color != -1) {
            attron(COLOR_PAIR(color));
            mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
            attroff(COLOR_PAIR(color));
        }else{
            mvwaddstr(screen, (y+ BORDER_TOP), (x + BORDER_LEFT), s.c_str());
        }
    }
        
    void addStringAtBoard(std::string s, int x, int y, WINDOW*& screen){
        addStringAtBoard(s,x,y,-1,screen);
    }

}

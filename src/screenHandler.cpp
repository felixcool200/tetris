#include <screenHandler.hpp>
#include <common.hpp>
#include <game.hpp>
#include <ncurses.h>
#include <string_view>
#include <string>

namespace ScreenHandler{
    void addCharAt(char ch, int x, int y, tetris::Color color, WINDOW*& screen){

        const bool useColor = (has_colors() == TRUE && color != tetris::Color::NONE);
        if (useColor)
            attron(COLOR_PAIR(color));

        mvwaddch(screen, y, x, ch);

        if (useColor)
            attroff(COLOR_PAIR(color));   
    }

    void addCharAtBoard(char ch, int x, int y, tetris::Color color, WINDOW*& screen){
        if(!Game::isOnBoard(x,y))
            return;
        addCharAt(ch, (x + tetris::BORDER_LEFT),(y+ tetris::BORDER_TOP), color, screen);
    }
    
    void addStringAt(std::string_view s, int x, int y, tetris::Color color, WINDOW*& screen){
        const bool useColor = (has_colors() == TRUE && color != tetris::Color::NONE);

        if (useColor)
            attron(COLOR_PAIR(color));

        mvwaddstr(screen, y, x, std::string(s).c_str());

        if (useColor)
            attroff(COLOR_PAIR(color));
    }
          
    void addStringAtBoard(std::string_view s, int x, int y, tetris::Color color, WINDOW*& screen){
        if(!Game::isOnBoard(x,y))
            return;
        addStringAt(s,x+tetris::BORDER_LEFT,y+tetris::BORDER_TOP,color,screen);
    }

}

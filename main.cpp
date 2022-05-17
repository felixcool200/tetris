#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>

// For sleep
#include <unistd.h>

//Blocks
#include "board.h"
//#include "block.h"
//#include "shape.h"

//Convertion for usleep
const int microsecondTosecond = 1000000; 

/* Structure
 * board owns a block
 * a block is the currently moving piece
 * a block has a shape
*/

int mainLoop(){
	int ch = getch();
	int delay = 0, height = 0, width = 0;
	Board board;
	while(true) {
		while(delay <= 10){
			if ((ch = getch()) != ERR) {
				board.update(ch);
				move(10, 10);
				addch(ch);
				addstr("Width: ");
				addch(width + '0');
				addstr("Height : ");
				addch(height + '0');
				refresh();
				if(ch == 'q'){
					addstr("QUITED");
					usleep(1*microsecondTosecond);
					endwin();
					return 0;
				}
			}
			delay += 1;
			usleep(10); //This makes the game MUCH less blocking and thread locking  
			getmaxyx(stdscr, height, width);
		}
		delay = 0;
		refresh();
    }
}

int main(){
	initscr(); // Create the screen
	cbreak(); // One char at a time
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters

	nodelay(stdscr, TRUE); // Read inputs all the time.
	return mainLoop();
}

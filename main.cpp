#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>

#define UI_WIDTH 0
#define UI_HEIGHT 0

// For sleep
#include <unistd.h>

//Blocks
#include "board.h"
//#include "block.h"
//#include "shape.h"

//Timing
//#include <chrono>
#include "timer.h"

//Convertion for usleep
const int microsecondTosecond = 1000000; 
const double secoundsPerFrame = 1.0/60.0;

/* Structure
 * board owns a block
 * a block is the currently moving piece
 * a block has a shape
*/

int mainLoop(){
	int ch = getch();
	int delay = 0, height = 0, width = 0;
	Board board;
	Timer timer(false);
	while(true) {
		//while(delay <= 10){
			timer.start();
			if ((ch = getch()) != ERR) {
				board.update(ch);
				board.draw(stdscr);
				move(10, 10);
				addch(ch);
				if(ch == 'q'){
					//addstr("QUITED");
					//usleep(1*microsecondTosecond);
					endwin();
					std::cout << "Terminated" << std::endl;
					return 0;
				}
			}
			//delay += 1;
			getmaxyx(stdscr, height, width); // Se if the terminal changed size
			refresh();
			double deltaTime = (secoundsPerFrame - timer.stop())*microsecondTosecond;
			if(deltaTime <= 0){
				endwin();
				std::cout << "Error: Game to slow for 60 fps" << std::endl;
				return 0;
			}
			usleep(deltaTime);
			//usleep(10); //This minimizes the CPU usage for the thread
		//}
		//delay = 0;
		//refresh();
    }
}

int main(){
	initscr(); // Create the screen
	cbreak(); // One char at a time
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters
	int height, width;
	getmaxyx(stdscr, height, width);
	if(height < BOARD_HEIGHT + UI_HEIGHT + 2 || width < BOARD_WIDTH + UI_WIDTH +  2){
		endwin();
		std::cout << "To small terminal" << std::endl;
		std::cout << "Height: " << height << ", Width: " << width << std::endl;
		return 0;
	}
	nodelay(stdscr, TRUE); // Read inputs all the time.
	return mainLoop();
}

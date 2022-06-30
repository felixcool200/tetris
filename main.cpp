#include <iostream>
#include <vector>
#include <ncurses.h>
#include <string>

#include "constants.h"

// For sleep
#include <unistd.h>

//Blocks
#include "board.h"

//UI
#include "ui.h"
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

void update(int input, Board board, UI ui){
	clear();
	board.update(input);
	ui.update();
	board.draw(stdscr);
	ui.draw(stdscr);
	refresh();
}

int mainLoop(){
	int ch = ERR;
	int delay, height = 0, width = 0;
	Board board;
	UI ui;
	Timer timer(false);
	while(true) {
		//while(delay <= 10){
			timer.start();
			if ((ch = getch()) != ERR) {
				delay = 0;
				update(ch, board, ui);
				if(ch == 'q'){
					endwin();
					std::cout << "Terminated" << std::endl;
					return 0;
				}
				refresh();
			}
			if(delay == 10){
				delay = 0;
				board.tick();
				update(-1, board, ui);
			}
			delay++;
			//getmaxyx(stdscr, height, width); // Se if the terminal changed size
			double deltaTime = (secoundsPerFrame - timer.stop())*microsecondTosecond;
			if(deltaTime <= 0){
				endwin();
				std::cout << "Error: Game to slow for 60 fps" << std::endl;
				return 0;
			}
			usleep(deltaTime);
    }
}

int main(){
	timeout(-1); // Do not wait for input
	//cbreak(); // One char at a time
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters
	initscr(); // Create the screen
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

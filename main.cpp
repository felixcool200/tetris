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

void update(int input, Board &board, UI &ui){
	clear();
	board.update(input);
	ui.update();
	board.draw(stdscr);
	ui.draw(stdscr);
	refresh();
}

void tick(Board &board, UI &ui){
	clear();
	board.tick();
	ui.update();
	board.draw(stdscr);
	ui.draw(stdscr);
	refresh();
}

int mainLoop(){
	int ch = ERR;
	int delay = 0 , height = 0, width = 0;
	Board board;
	UI ui;
	Timer timer(false);
	while(true) {
		timer.start();
		if ((ch = getch()) != ERR) {
			//delay = 0;
			update(ch, board, ui);
			if(ch == 'q'){
				endwin();
				std::cout << "Terminated" << std::endl;
				return 0;
				break;
			}
			refresh();
		}
		if(delay == DELAY){
			delay = 0;
			tick(board, ui); // Tick down
		}
		if(board.isGameOver()){
			endwin();
			std::cout << "Game over" << std::endl;
			return 0;
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

bool initNCURSES(){
	timeout(-1); // Do not wait for input
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters
	initscr(); // Create the screen
	start_color();
	//init_pair(COLOR_BLOCK_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_BLOCK_RED, COLOR_RED, COLOR_RED);
    init_pair(COLOR_BLOCK_GREEN, COLOR_GREEN, COLOR_GREEN);
    init_pair(COLOR_BLOCK_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(COLOR_BLOCK_BLUE, COLOR_BLUE, COLOR_BLUE);
	init_pair(COLOR_BLOCK_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(COLOR_BLOCK_CYAN, COLOR_CYAN, COLOR_CYAN);
	init_pair(COLOR_BLOCK_WHITE, COLOR_WHITE, COLOR_WHITE);

	nodelay(stdscr, TRUE); // Read inputs all the time.
	
	int height, width;
	getmaxyx(stdscr, height, width);
	if(height < BOARD_HEIGHT + UI_HEIGHT + 2 || width < BOARD_WIDTH + UI_WIDTH +  2){
		endwin();
		std::cout << "To small terminal" << std::endl;
		std::cout << "Height: " << height << ", Width: " << width << std::endl;
		return -1;
	}

	if (has_colors() == FALSE) {
		endwin();
		std::cout << "Your terminal does not support color" << std::endl;
		return -1;
	}
	return 0;
}

int main(){
	//cbreak(); // One char at a time
	srand(4);
	if(initNCURSES() == -1){
		return -1;
	}
	return mainLoop();
}

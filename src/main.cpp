#include <iostream>
//#include <vector>
#include <ncurses.h>
#include <string>
// For sleep
#include <unistd.h>

#include "../include/constants.hpp"

//Blocks
#include "../include/board.hpp"

//UI
#include "../include/ui.hpp"
//#include "../include/block.h"
//#include "../include/shape.h"

//Timing
//#include <chrono>
#include "../include/timer.hpp"

//Convertion for usleep
const int microsecondTosecond = 1000000; 
const double secoundsPerFrame = 1.0/60.0;

/* Structure
 * board owns a block
 * a block is the currently moving piece
 * a block has a shape
*/

void updateUI(Board &board){
	board.draw(stdscr);
	UI::draw(stdscr, board.getHold(),board.getNext(),board.getScore(),board.getLines());
	refresh();
}

void update(char input, Board &board){
	clear();
	board.update(input);
	updateUI(board);
}

void tick(Board &board){
	clear();
	board.tick();
	updateUI(board);
}

int mainLoop(){
	char ch = ERR;
	int delay_in_frames = 0 , height = 0, width = 0;
	Board board;
	Timer timer(false);
	updateUI(board);
	while(true) {
		timer.start();
		if ((ch = getch()) != ERR) {
			if(ch == 'q' || ch == 'Q'){
				//endwin();
				//std::cout << "Terminated" << std::endl;
				break;
			}
			update(ch, board);
			//Reset clock for the new block. Stops the first tick of block placed manually "via pressing space" to be random.
			if(board.wasBlockJustPlaced()){
				delay_in_frames = 0;
			}
			refresh();
		}

		// Game the block move (This controlles the speed)
		if(delay_in_frames == int(board.getFramesPerTick())){
			delay_in_frames = 0;
			tick(board); // Tick down
		}
		if(board.isGameOver()){
			//endwin();
			//std::cout << "Game over" << std::endl;
			//return 0;
			break;
		}
		delay_in_frames++;
		//getmaxyx(stdscr, height, width); // Se if the terminal changed size
		double deltaTime = (secoundsPerFrame - timer.stop())*microsecondTosecond;
		if(deltaTime <= 0){
			endwin();
			std::cout << "Error: Game to slow for 60 fps" << std::endl;
			break;
			//return 0;
		}
		usleep(deltaTime);
    }
	endwin();
	exit_curses;
	delwin(stdscr);
	std::cout << "Game over \nResult:\nLines cleared:" << board.getLines() << "\nScore: " << board.getScore() << std::endl;
	return 0;
}

int initNCURSES(){
	timeout(-1); // Do not wait for input
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters
	initscr(); // Create the screen
	curs_set(0);
	start_color();
	init_pair(COLOR_BLOCK_BLACK, COLOR_BLACK, COLOR_BLACK);
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
	srand(1);
	if(initNCURSES() == -1){
		return -1;
	}
	return mainLoop();
}

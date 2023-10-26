#include <iostream>
//#include <vector>
#include <ncurses.h>
#include <string>
// For sleep
#include <unistd.h>
#include <stdlib.h>		 /* srand, rand */
#include <random>

#include "../include/constants.hpp"
//const bool (*PIECES[TETROMINOS])[SHAPESIZE][SHAPESIZE] = {&O_PIECE, &I_PIECE, &S_PIECE, &Z_PIECE, &L_PIECE, &J_PIECE, &T_PIECE};

//Blocks
#include "../include/game.hpp"

//UI
#include "../include/ui.hpp"
//#include "../include/block.h"
//#include "../include/shape.h"

//Timing
//#include <chrono>
#include "../include/timer.hpp"

/* Structure
 * game owns a block
 * a block is the currently moving piece
 * a block has a shape
*/

void updateUI(Game &game){
	game.draw();
	UI::draw(game.getHold(),game.getNext(),game.getScore(),game.getLines(),game.getLevel());
	refresh();
}

int update(char input, Game &game){
	clear();
	int val = game.update(input);
	updateUI(game);
	return val;
}

void tick(Game &game){
	clear();
	game.tick();
	updateUI(game);
}

void initColors(){
	//Block Colors
	init_pair(COLOR_TETROMINO_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_TETROMINO_RED, COLOR_RED, COLOR_RED);
	init_pair(COLOR_TETROMINO_GREEN, COLOR_GREEN, COLOR_GREEN);
	init_pair(COLOR_TETROMINO_YELLOW, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(COLOR_TETROMINO_BLUE, COLOR_BLUE, COLOR_BLUE);
	init_pair(COLOR_TETROMINO_MAGENTA, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(COLOR_TETROMINO_CYAN, COLOR_CYAN, COLOR_CYAN);
	init_pair(COLOR_TETROMINO_WHITE, COLOR_WHITE, COLOR_WHITE);

	// Text Colors
	init_pair(COLOR_TEXT_BLACK, COLOR_BLACK, COLOR_BLACK);
	init_pair(COLOR_TEXT_RED, COLOR_RED, COLOR_BLACK);
	init_pair(COLOR_TEXT_GREEN, COLOR_GREEN, COLOR_BLACK);
	init_pair(COLOR_TEXT_YELLOW, COLOR_YELLOW, COLOR_BLACK);
	init_pair(COLOR_TEXT_BLUE, COLOR_BLUE, COLOR_BLACK);
	init_pair(COLOR_TEXT_MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(COLOR_TEXT_CYAN, COLOR_CYAN, COLOR_BLACK);
	init_pair(COLOR_TEXT_WHITE, COLOR_WHITE, COLOR_BLACK);

	// Preview Colors
	const int FACTOR = 500;
	init_color(COLOR_PREVIEW_RED    ,FACTOR,0,0);
	init_color(COLOR_PREVIEW_GREEN  ,0,FACTOR,0);
	init_color(COLOR_PREVIEW_YELLOW ,FACTOR,FACTOR,0);
	init_color(COLOR_PREVIEW_BLUE   ,0,0,FACTOR);
	init_color(COLOR_PREVIEW_MAGENTA,FACTOR,0,FACTOR);
	init_color(COLOR_PREVIEW_CYAN   ,0,FACTOR,FACTOR);
	init_color(COLOR_PREVIEW_WHITE  ,FACTOR,FACTOR,FACTOR);

	init_pair(COLOR_PREVIEW_RED, COLOR_PREVIEW_RED, COLOR_PREVIEW_RED);
	init_pair(COLOR_PREVIEW_GREEN, COLOR_PREVIEW_GREEN, COLOR_PREVIEW_GREEN);
	init_pair(COLOR_PREVIEW_YELLOW, COLOR_PREVIEW_YELLOW, COLOR_PREVIEW_YELLOW);
	init_pair(COLOR_PREVIEW_BLUE, COLOR_PREVIEW_BLUE, COLOR_PREVIEW_BLUE);
	init_pair(COLOR_PREVIEW_MAGENTA, COLOR_PREVIEW_MAGENTA, COLOR_PREVIEW_MAGENTA);
	init_pair(COLOR_PREVIEW_CYAN, COLOR_PREVIEW_CYAN, COLOR_PREVIEW_CYAN);
	init_pair(COLOR_PREVIEW_WHITE, COLOR_PREVIEW_WHITE, COLOR_PREVIEW_WHITE);
}

int mainLoop(){

	std::random_device os_seed;
	srand(os_seed());
	
	char ch = ERR;
	int delay_in_frames = 0 , height = 0, width = 0;
	Game game;
	Timer timer(false);

	updateUI(game);
	while(true) {
		timer.start();
		if ((ch = getch()) != ERR) {
			if(update(ch, game) == -1){
				break;
			}
			//Reset clock for the new block. Stops the first tick of block placed manually "via pressing space" to be random.
			if(game.wasTetrominoJustPlaced()){
				delay_in_frames = 0;
			}
			//refresh();
			updateUI(game);
		}

		// Game the block move (This controlles the speed)
		if(delay_in_frames == int(game.getFramesPerTick())){
			delay_in_frames = 0;
			tick(game); // Tick down
		}
		if(game.isGameOver()){
			break;
		}
		delay_in_frames++;
		//getmaxyx(stdscr, height, width); // Se if the terminal changed size
		double deltaTime = (secoundsPerFrame - timer.stop())*microsecondTosecond;
		if(deltaTime <= 0){
			endwin();
			std::cout << "Error: Game to slow for "<< 1/secoundsPerFrame << " fps" << std::endl;
			return -1;
		}
		usleep(deltaTime);
    }
	endwin();
	exit_curses;
	delwin(stdscr);
	std::cout << "Game over \nResult:\nLines cleared:" << game.getLines() << "\nScore: " << game.getScore() << std::endl;
	return 0;
}

int initNCURSES(){
	timeout(-1); // Do not wait for input
	noecho(); // Dont echo key pressed
	keypad(stdscr, TRUE); //enable "special" characters
	curs_set(0);
	initscr(); // Create the screen
	start_color();
	initColors();
	
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

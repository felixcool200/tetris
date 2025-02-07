#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

#include <random>

#include <thread>
#include <chrono>

#include <ncurses.h>

#include <common.hpp>
#include <game.hpp>
#include <timer.hpp>
#include <ui.hpp>

/* Structure
 * game owns a block
 * a block is the currently moving piece
 * a block has a shape
*/

void redrawFrame(Game &game){
	clear();
	game.draw();
	UI::draw(game.getHold(),game.getNext(),game.getScore(),game.getLines(),game.getLevel());
	refresh(); //Redraw the ncurses screen
}

void initColors(){
	//Block Colors
	using namespace tetris;
	// Initilize new colors
	const int FACTOR = 500;

	const std::vector<std::tuple<NcurseColor, short, short, short>> newColors = {
		{NcurseColor::PREVIEW_RED     ,FACTOR, 0,      0},
		{NcurseColor::PREVIEW_GREEN   ,0,      FACTOR, 0},
		{NcurseColor::PREVIEW_YELLOW  ,FACTOR, FACTOR, 0},
		{NcurseColor::PREVIEW_BLUE    ,0,      0,      FACTOR},
		{NcurseColor::PREVIEW_MAGENTA ,FACTOR, 0,      FACTOR},
		{NcurseColor::PREVIEW_CYAN    ,0,      FACTOR, FACTOR},
		{NcurseColor::PREVIEW_WHITE   ,FACTOR, FACTOR, FACTOR},
	};

	const std::vector<std::tuple<Color, NcurseColor, NcurseColor>> colors = {
		//TETROMINO Colors
		{Color::TETROMINO_BLACK,   NcurseColor::BLACK,	 NcurseColor::BLACK},
		{Color::TETROMINO_RED, 	   NcurseColor::RED,	 NcurseColor::RED},
		{Color::TETROMINO_GREEN,   NcurseColor::GREEN,	 NcurseColor::GREEN},
		{Color::TETROMINO_YELLOW,  NcurseColor::YELLOW,	 NcurseColor::YELLOW},
		{Color::TETROMINO_BLUE,    NcurseColor::BLUE,	 NcurseColor::BLUE},
		{Color::TETROMINO_MAGENTA, NcurseColor::MAGENTA, NcurseColor::MAGENTA},
		{Color::TETROMINO_CYAN,    NcurseColor::CYAN,	 NcurseColor::CYAN},
		{Color::TETROMINO_WHITE,   NcurseColor::WHITE,	 NcurseColor::WHITE},

		//TEXT Colors
		{Color::TEXT_BLACK,	  NcurseColor::BLACK,   NcurseColor::BLACK},
		{Color::TEXT_RED,	  NcurseColor::RED,     NcurseColor::BLACK},
		{Color::TEXT_GREEN,	  NcurseColor::GREEN,   NcurseColor::BLACK},
		{Color::TEXT_YELLOW,  NcurseColor::YELLOW,  NcurseColor::BLACK},
		{Color::TEXT_BLUE,    NcurseColor::BLUE,    NcurseColor::BLACK},
		{Color::TEXT_MAGENTA, NcurseColor::MAGENTA, NcurseColor::BLACK},
		{Color::TEXT_CYAN,	  NcurseColor::CYAN,    NcurseColor::BLACK},
		{Color::TEXT_WHITE,	  NcurseColor::WHITE,   NcurseColor::BLACK},

		//TETROMINO Preview Colors
		{Color::PREVIEW_RED, 	 NcurseColor::PREVIEW_RED, 	   NcurseColor::PREVIEW_RED},
		{Color::PREVIEW_GREEN,   NcurseColor::PREVIEW_GREEN,   NcurseColor::PREVIEW_GREEN},
		{Color::PREVIEW_YELLOW,  NcurseColor::PREVIEW_YELLOW,  NcurseColor::PREVIEW_YELLOW},
		{Color::PREVIEW_BLUE,    NcurseColor::PREVIEW_BLUE,    NcurseColor::PREVIEW_BLUE},
		{Color::PREVIEW_MAGENTA, NcurseColor::PREVIEW_MAGENTA, NcurseColor::PREVIEW_MAGENTA},
		{Color::PREVIEW_CYAN,    NcurseColor::PREVIEW_CYAN,    NcurseColor::PREVIEW_CYAN},
		{Color::PREVIEW_WHITE,   NcurseColor::PREVIEW_WHITE,   NcurseColor::PREVIEW_WHITE},
	};

	for(const auto& color: newColors)
		init_color((ColorTools::enumToValue(static_cast<Color>(std::get<0>(color)))), 
			static_cast<short>(std::get<1>(color)),
			static_cast<short>(std::get<2>(color)),
			static_cast<short>(std::get<3>(color)));

	for(const auto& color: colors)
		init_pair((ColorTools::enumToValue(static_cast<Color>(std::get<0>(color)))), 
			static_cast<short>(std::get<1>(color)),
			static_cast<short>(std::get<2>(color)));

}


int mainLoop(){
	char ch = ERR;
	int delay_in_frames = 0 , height = 0, width = 0;
	bool redrawThisFrame = false;
	
	Game game;
	Timer timer(false);

	redrawFrame(game);
	while(true) {
		//The frame timer starts here
		timer.start();
		
		//Check if a key is pressed
		if ((ch = getch()) != ERR) {
			auto keyPressed = tetris::ControlTools::valueToEnum(ch);
			game.update(keyPressed); 
			if(game.isGameOver()){
				break;
			}

			//Reset clock for the new block. Stops the first tick of block placed manually "via pressing space" to be random.
			//Can only happen after a key is pressed
			if(game.wasTetrominoJustPlaced()){
				delay_in_frames = 0;
			}
			redrawThisFrame = true;
		}

		//Check if it is time for the block to fall one space
		if(delay_in_frames == game.getFramesPerTick()){
			redrawThisFrame = true;
			delay_in_frames = 0;
			
			game.tick();
			if(game.isGameOver()){
				break;
			}
		}else{
			++delay_in_frames;
		}
		
		if(redrawThisFrame){
			redrawFrame(game);
			redrawThisFrame = false;
		}

		std::chrono::duration<double> deltaTime = (tetris::frameDuration - std::chrono::duration_cast<std::chrono::microseconds>(timer.stop()));

		if(deltaTime.count() < 0){
			endwin();
			std::cout << "Error: Game to slow for "<< 1/std::chrono::duration_cast<std::chrono::seconds>(tetris::frameDuration).count() << " fps " << deltaTime <<  std::endl;
			return -1;
		}
		std::this_thread::sleep_for(deltaTime);
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
	if(height < tetris::BOARD_HEIGHT + tetris::UI_HEIGHT + 2 || width < tetris::BOARD_WIDTH + tetris::UI_WIDTH +  2){
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

	if(initNCURSES() == -1){
		return -1;
	}
	return mainLoop();
}

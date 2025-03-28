#include <common.hpp>
#include <game.hpp>
#include <timer.hpp>

#include <screenInterface.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#include <ScreenToUse.hpp>

template<typename screenInterface>
requires Screen::ScreenInterface<screenInterface>  // Ensure Screen implements the required interface
int mainLoop() {
	using namespace std::chrono_literals;
	int delay_in_frames = 0;
	bool redrawThisFrame = false, isPaused = false;

	if (screenInterface::initScreen() == Screen::StatusCode::ERROR) {
		return -1;
	}

	Game<screenInterface> game;
	Timer timer(false);
	
	game.draw();
	while(true) {
		
		//The frame timer starts here
		timer.start();
		
		//Check if a key is pressed
		if (auto keyPressed = screenInterface::getInput(); keyPressed != tetris::Control::NONE) {
			if (keyPressed == tetris::Control::PAUSE_KEY) {
				isPaused = !isPaused;
			}
			if (isPaused) {
				continue;
			}
			game.update(keyPressed);
			if (game.isGameOver()) {
				break;
			}
			
			//Reset clock for the new block. Stops the first tick of block placed manually "via pressing space" to be random.
			//Can only happen after a key is pressed
			if (game.wasTetrominoJustPlaced()) {
				delay_in_frames = 0;
			}
			redrawThisFrame = true;
		}
		
		if (isPaused) {
			std::this_thread::sleep_for(0.1s);
			continue;
		}
		
		//Check if it is time for the block to fall one space
		if (delay_in_frames == game.getFramesPerTick()) {
			redrawThisFrame = true;
			delay_in_frames = 0;
			
			game.tick();
			if (game.isGameOver()) {
				break;
			}
		} else {
			++delay_in_frames;
		}
		
		if (redrawThisFrame) {
			game.draw();
			redrawThisFrame = false;
		}
		
		std::chrono::duration<double> deltaTime = (tetris::frameDuration - std::chrono::duration_cast<std::chrono::microseconds>(timer.stop()));
		
		if (deltaTime.count() < 0) {
			if (screenInterface::closeScreen() == Screen::StatusCode::ERROR) {
				return -1;
			}
			std::cout << "Error: Game to slow for "<< 1/tetris::frameDuration.count() << " fps " << deltaTime.count() <<  std::endl;
			return -1;
		}
		std::this_thread::sleep_for(deltaTime);
	}
	if (screenInterface::closeScreen() == Screen::StatusCode::ERROR) {
		return -1;
	}
	std::cout << "Game over \nResult:\nLines cleared:" << game.getLines() << "\nScore: " << game.getScore() << std::endl;
	return 0;
}

int main() {
	return mainLoop<NcursesScreen>();
}
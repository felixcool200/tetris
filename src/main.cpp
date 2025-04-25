#include <common.hpp>
#include <game.hpp>
#include <timer.hpp>

#include <screenInterface.hpp>
#include <iostream>
#include <thread>
#include <chrono>

#include <ScreenToUse.hpp>

template<typename screenInterface> requires Screen::ScreenInterface<screenInterface>
int mainLoop() {
	using namespace std::chrono_literals;
	int delay_in_frames = 0;
	bool isPaused = false;

	if (screenInterface::initScreen() == Screen::StatusCode::ERROR) {
		return -1;
	}

	Game<screenInterface> game;
	Timer timer(false);
	
	screenInterface::clearScreen(); // Clear the screen
	game.render();
	screenInterface::redrawScreen(); // Redraw the screen
	int frame = 0;
	while(true) {
		
		// The frame timer starts here
		frame++;
		timer.start();
		
		// Check if a key is pressed
		if (auto keyPressed = screenInterface::getInput(); keyPressed != tetris::Control::NONE) {
			// Handle toggling of paused menu.
			if (keyPressed == tetris::Control::PAUSE) {
				isPaused = !isPaused;
			}

			// Do not process other input if game is paused
			if (isPaused) {
				continue;
			}

			// Process keypress
			game.update(keyPressed);

			// Quit if game is over
			if (game.isGameOver()) {
				break;
			}
			
			// Reset clock for the new block. Stops the first tick of block placed manually "via pressing space" to be random.
			// Can only happen after a key is pressed
			if (game.wasTetrominoJustPlaced()) {
				delay_in_frames = 0;
			}
		}
		
		if (isPaused) {
			screenInterface::clearScreen(); // Clear the screen
			game.renderPauseScreen();
			screenInterface::redrawScreen(); // Redraw the screen
			std::this_thread::sleep_for(50ms);
			continue;
		}
		
		//Check if it is time for the block to fall one space
		if (delay_in_frames == game.getFramesPerTick()) {
			delay_in_frames = 0;
			
			game.tick();
			if (game.isGameOver()) {
				break;
			}
		} else {
			++delay_in_frames;
		}
		
		screenInterface::clearScreen(); // Clear the screen
		game.render();
		screenInterface::redrawScreen(); // Redraw the screen

		std::chrono::duration<double> deltaTime = (tetris::frameDuration - std::chrono::duration_cast<std::chrono::microseconds>(timer.stop()));
		// Allow first frame to be slow/late
		if (deltaTime.count() < 0) {
			if(frame > 5){
				screenInterface::closeScreen();
			}
			std::cout << "Error: Game to slow for " << tetris::fps << " fps " << std::chrono::duration_cast<std::chrono::milliseconds>(deltaTime).count() << "ms" << std::endl;
			std::cout << "Late frame: " << frame << std::endl;
			if(frame > 5){
				return -1;
			}
		}
		std::this_thread::sleep_for(deltaTime);
	}

	if (screenInterface::closeScreen() == Screen::StatusCode::ERROR) {
		return -1;
	}
	
	std::cout << game.getResult() << std::endl;
	return 0;
}

int main() {
	return mainLoop<ScreenType>();
}
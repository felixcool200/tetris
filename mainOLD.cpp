#include <iostream>
#include <chrono>
#include <thread>

using namespace std::literals::chrono_literals;

static bool running = false;
int boardSize = 10;
int posX = 0;
int posY = 0;

void update(){
    	std::cout << "\033[2J\033[1;1H";    
    	char board[10][10];
		if(posX >= 10 || posY >= 10){
			running = false;
			return;
		}
    	for(int i = 0; i < 10;i++){
           	for(int j = 0; j < 10;j++){
                	board[i][j] = '@';
                	board[posX][posY] = 'P';
                	std::cout << board[i][j];
            	}  
       	std::cout << "\n";
    	} 
}

void inputLoop(){
	char key;
	while(true){
		std::cin >> key;
		switch(key){
		case 'w':
			posX--;
			break;
		case 'a':
			posY--;
			break;}
	}
}


void run(){
    running = true; 
	while(running){
		std::this_thread::sleep_for(1s);
		posX += 1;
		posY += 1;
		update();
    }
	return;
}


int main(){
    std::cout << "Hello World" << std::endl;
    std::cout << "This is Tetris" << std::endl;	
	std::thread gameThread(run);
	inputLoop();
	return 0;
}

#include <iostream>
#include <chrono>
#include <string>

using namespace std;

bool running = false;
int boardSize = 10;

class block{
public:
int x = 0;
int y = 0;
void MoveBlock(){
    if(y > boardSize){
    y++;
    }
}
};

void update(block o){ 
    cout << "\033[2J\033[1;1H";    
    char board[10][10];
    for(int i = 0; i < 10;i++){
           for(int j = 0; j < 10;j++){
                board[i][j] = '@';
                board[o.y][o.x] = 'P';
                cout << board[i][j];
        }  
        cout << "\n";
    } 
}

void run(){
    running = true;
    auto previous = chrono::high_resolution_clock::now();
    block obj1;
    while(running){
        auto now = chrono::high_resolution_clock::now();
        chrono::duration<double> D = now - previous;
        if(D.count() >= 1){
            previous = now;
            obj1.MoveBlock();
            update(obj1);}
    }
}

int main(){
    cout << "Hello World" << endl;
    cout << "This is Tetris" << endl;
    run();
    return 0;
}


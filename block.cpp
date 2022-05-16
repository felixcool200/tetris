#include "block.h"
#include <ncurses.h>
#include "shape.h"

Block::Block(){

}
Block::Block(int x, int y){

}
Block::Block(int x, int y, Shape shape){

}

void Block::rotateRight(){

}

void Block::move(int ch){
    switch (ch) {   
        //Rotate the Block
        case KEY_UP:
            this->rotateRight();
        break;

        //Speed up block
        case KEY_DOWN:
            m_y += 1;
        break;

        //Move block one step to the right
        case KEY_RIGHT:
            m_x += 1;
        break;

        //Move block one step to the left
        case KEY_LEFT:
            m_x -= 1;
        break;
     }
}

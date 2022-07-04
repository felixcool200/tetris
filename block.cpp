#include "block.h"
#include "shape.h"
#include "constants.h"
#include "ScreenHandler.h"

#include <iostream>

Block::Block(int x, int y){
    m_x = x;
    m_y = y;
    m_fast = false;
    m_shape = Shape();
}
Block::Block(int x, int y, Shape shape){

}

bool Block::getShape(int x, int y){
    return m_shape.getShape(x,y);
}

void Block::rotateRight(){
    m_shape.rotateRight();
}

int Block::getX(){
    return m_x;
}

int Block::getY(){
    return m_y;
}

void Block::tick(){
    m_y += 1;
}

void Block::move(int ch){
    switch (ch) {   
        //Rotate the Block
        case KEY_UP:
            this->rotateRight();
        break;

        //Speed up block
        case KEY_DOWN:
            m_fast = 1;
        break;

        //Move block one step to the right
        case KEY_RIGHT:
            if(m_x + 1 < BOARD_WIDTH - SHAPESIZE){
                m_x += 1;
            }
        break;

        //Move block one step to the left
        case KEY_LEFT:
            if(m_x >= 0){
                m_x -= 1;
            }
        break;
     }
     //m_y += 1;
}

void Block::draw(WINDOW*& screen){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int i = 0; i < SHAPESIZE; ++i){
        for(int j = 0; j < SHAPESIZE; ++j){
            if(m_shape.getShape(j,i)){
                ScreenHandler::addCharAtBoard(screen,'B',(m_x + j),(m_y + i));
            }
        }
        //ScreenHandler::moveCurserBoard(screen, m_y + i, m_x);
    }
}

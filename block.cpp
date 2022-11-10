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
    m_x = x;
    m_y = y;
    m_fast = false;
    m_shape = shape;
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
    m_fast = false;
    switch (ch) {   
        //Rotate the Block
        case KEY_UP:
        case 'w':
            this->rotateRight();
        break;

        //Speed up block
        case KEY_DOWN:
        case 's':
            m_fast = true;
        break;

        //Move block one step to the right
        case KEY_RIGHT:
        case 'd':
            m_x += 1;
            if(m_x <= BOARD_WIDTH - this->mostRightOffset()){
            }
        break;

        //Move block one step to the left
        case KEY_LEFT:
        case 'a':
            m_x -= 1;
            if(m_x >= 0 + this->mostLeftOffset()){
            }
        break;
     }
}

int Block::mostLeftOffset(){
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.getShape(dy,dy)){
                return dx;
            }
        }
    }
}

int Block::mostRightOffset(){
    for(int dx = SHAPESIZE; dx > 0; --dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.getShape(dy,dy)){
                return dx;
            }
        }
    }
}

void Block::draw(WINDOW*& screen){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.getShape(dx,dy)){
                ScreenHandler::addCharAtBoard(screen,'B',(m_x + dx),(m_y + dy));
            }
        }
        //ScreenHandler::moveCurserBoard(screen, m_y + i, m_x);
    }
}

// Functions

Block testMove(Block bl, int ch){
    // Make sure it is a copy of bl
    bl.move(ch);
    return bl;
}

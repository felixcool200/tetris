#include "block.h"
#include "shape.h"
#include "constants.h"
#include "ScreenHandler.h"

#include <iostream>
Block::Block(int x, int y, bool held){
    m_shape = Shape();
    m_x = x;
    m_y = y;
    m_beenHeld = held;
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

int Block::getColor(){
    return m_shape.getColor();;
}

void Block::tick(){
    m_y += 1;
}

bool Block::hasBeenHeld(){
    return m_beenHeld;
}

void Block::hold(){
    reset();
    m_beenHeld = true;
}

void Block::reset(){
    m_x = (BOARD_WIDTH-SHAPESIZE)/2;
    m_y = -1;
    m_shape.reset();
}

void Block::move(int ch){
    switch (ch) {   
        //Rotate the Block
        case KEY_UP:
        case 'w':
            this->rotateRight();
        break;

        //Speed up block
        case KEY_DOWN:
        case 's':
            m_y += 1;
        break;

        //Move block one step to the right
        case KEY_RIGHT:
        case 'd':
            m_x += 1;
        break;

        //Move block one step to the left
        case KEY_LEFT:
        case 'a':
            m_x -= 1;
        break;
     }
}

void Block::draw(WINDOW*& screen){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.getShape(dx,dy)){
                ScreenHandler::addCharAtBoard(screen,'B',(m_x + dx),(m_y + dy), this->getColor());
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

Block testTick(Block bl){
    // Make sure it is a copy of bl
    bl.tick();
    return bl;
}
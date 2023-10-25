#include "../include/block.hpp"
#include "../include/shape.hpp"
#include "../include/constants.hpp"
#include "../include/screenHandler.hpp"

#include <iostream>
Block::Block(int x, int y, bool held){
    m_shape = Shape();
    m_x = x;
    m_y = y;
    m_beenHeld = held;
}

Block::Block(const Block &o){
    m_shape = o.m_shape;
    m_x = o.m_x;
    m_y = o.m_y;
    m_beenHeld = o.m_beenHeld;
}
bool Block::isFilledAt(int x, int y){
    return m_shape.isFilledAt(x,y);
}

char Block::getShape(){
    return m_shape.getShape();
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
        case ROTATE_BLOCK_KEY:
            this->rotateRight();
        break;

        //Speed up block
        //TODO: Change this to a factor(2) that is multiplied when a tick is performed.
        case MOVE_DOWN_KEY:
            m_y += 1;
        break;

        //Move block one step to the right
        case MOVE_RIGHT_KEY:
            m_x += 1;
        break;

        //Move block one step to the left
        case MOVE_LEFT_KEY:
            m_x -= 1;
        break;
     }
}

void Block::draw(WINDOW*& screen){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.isFilledAt(dx,dy)){
                ScreenHandler::addColoredCharAtBoard('B',(m_x + dx),(m_y + dy), this->getColor(),screen);
            }
        }
    }
}

void Block::drawAt(WINDOW*& screen,int x, int y){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(m_shape.isFilledAt(dx,dy)){
                ScreenHandler::addColoredCharAt('B',(x + dx),(y + dy), this->getColor(),screen);
            }
        }
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

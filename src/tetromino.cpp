#include "../include/tetromino.hpp"
#include "../include/constants.hpp"
#include "../include/screenHandler.hpp"

#include <iostream>
Tetromino::Tetromino(int x, int y, bool held){
    m_shapeIndex = rand() % TETROMINOS;
    m_direction = DEFAULT_SHAPE_DIRECTION;
    m_x = x;
    m_y = y;
    m_beenHeld = held;
}

Tetromino::Tetromino(const Tetromino &o){
    m_shapeIndex = o.m_shapeIndex;
    m_direction = o.m_direction;
    m_x = o.m_x;
    m_y = o.m_y;
    m_beenHeld = o.m_beenHeld;
}


/*
    https://stackoverflow.com/questions/37812817/finding-element-at-x-y-in-a-given-matrix-after-rotation-in-c-c
    m_direction = 0
            0 1 2 3
            4 5 6 7
            8 9 A B
            C D E F

    m_direction = 1
            C 8 4 0
            D 9 5 1
            E A 6 2
            F B 7 3

    m_direction = 2
            F E D C
            B A 9 8
            7 6 5 4
            3 2 1 0

    m_direction = 3
            3 7 B F
            2 6 A E
            1 5 9 D
            0 4 8 C
*/
bool Tetromino::isFilledAt(int x, int y){
    switch (m_direction)
	{
		case 0:
			return PIECES[m_shapeIndex][x][y];
		case 1:
			return PIECES[m_shapeIndex][y][SHAPESIZE - 1 - x];
		case 2:
			return PIECES[m_shapeIndex][SHAPESIZE - 1 - x][SHAPESIZE - 1 - y];
		case 3:
			return PIECES[m_shapeIndex][SHAPESIZE - 1 - y][SHAPESIZE - 1 - (SHAPESIZE - 1 - x)];
        default:
	        return PIECES[m_shapeIndex][x][y]; // Default is zero rotation (should never happen) 
	}
    return PIECES[m_shapeIndex][x][y]; // Default is zero rotation (should never happen) 
}

char Tetromino::getShape(){
    switch (m_shapeIndex){
		case 0:
			return 'O';
		case 1:
			return 'I';
		case 2:
			return 'S';
		case 3:
			return 'Z';
		case 4:
			return 'L';
		case 5:
			return 'J';
		case 6:
			return 'T';
		}
	return 'O';
}

//To rotate left: m_direction = (m_direction - 1) % 4;
void Tetromino::rotateRight(){
    m_direction = (m_direction + 1) % 4;
}

int Tetromino::getX(){
    return m_x;
}

int Tetromino::getY(){
    return m_y;
}

int Tetromino::getColor(){
    return TETROMINO_COLORS[m_shapeIndex];
}

int Tetromino::getPreviewColor(){
	return PREVIEW_COLORS[m_shapeIndex];
}

void Tetromino::tick(){
    m_y += 1;
}

bool Tetromino::hasBeenHeld(){
    return m_beenHeld;
}

void Tetromino::hold(){
    reset();
    m_beenHeld = true;
}

void Tetromino::reset(){
    m_x = (BOARD_WIDTH-SHAPESIZE)/2;
    m_y = -1;
    m_direction = DEFAULT_SHAPE_DIRECTION;
}

void Tetromino::move(int ch){
    switch (ch) {   
        //Rotate the Tetromino
        case ROTATE_TETROMINO_KEY:
            this->rotateRight();
        break;

        //Speed up Tetromino
        //TODO: Change this to a factor(2) that is multiplied when a tick is performed.
        case MOVE_DOWN_KEY:
            m_y += 1;
        break;

        //Move Tetromino one step to the right
        case MOVE_RIGHT_KEY:
            m_x += 1;
        break;

        //Move Tetromino one step to the left
        case MOVE_LEFT_KEY:
            m_x -= 1;
        break;
     }
}

void Tetromino::draw(bool isPreview){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    int color = -1;

    if(isPreview){
        color = this->getPreviewColor();
    }else{
        color = this->getColor();
    }

    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(this->isFilledAt(dx,dy)){
                ScreenHandler::addCharAtBoard('B',(m_x + dx),(m_y + dy),color);
            }
        }
    }
}

void Tetromino::drawAt(int x, int y,bool isPreview){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < SHAPESIZE; ++dx){
        for(int dy = 0; dy < SHAPESIZE; ++dy){
            if(this->isFilledAt(dx,dy)){
                ScreenHandler::addCharAt('B',(x + dx),(y + dy), this->getColor());
            }
        }
    }
}

// Functions

Tetromino testMove(Tetromino bl, int ch){
    // Make sure it is a copy of bl
    bl.move(ch);
    return bl;
}

Tetromino testTick(Tetromino bl){
    // Make sure it is a copy of bl
    bl.tick();
    return bl;
}
#include <iostream>
#include <functional>

#include <tetromino.hpp>
#include <common.hpp>
#include <screenHandler.hpp>

Tetromino::Tetromino(int x, int y, bool held){
    m_shapeIndex = tetris::randomTetrominoIndex();
    m_direction = tetris::DEFAULT_SHAPE_DIRECTION;
    m_x = x;
    m_y = y;
    m_beenHeld = held;
}

/*Tetromino::Tetromino(const Tetromino &o){
    m_shapeIndex = o.m_shapeIndex;
    m_direction = o.m_direction;
    m_x = o.m_x;
    m_y = o.m_y;
    m_beenHeld = o.m_beenHeld;
}*/


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

bool Tetromino::isFilledAt(int x, int y) const{
    switch (m_direction)
	{
		case 0:
			return tetris::PIECES[m_shapeIndex][x][y];
		case 1:
			return tetris::PIECES[m_shapeIndex][y][tetris::SHAPESIZE - 1 - x];
		case 2:
			return tetris::PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - x][tetris::SHAPESIZE - 1 - y];
		case 3:
			return tetris::PIECES[m_shapeIndex][tetris::SHAPESIZE - 1 - y][tetris::SHAPESIZE - 1 - (tetris::SHAPESIZE - 1 - x)];
        default:
	        return tetris::PIECES[m_shapeIndex][x][y]; // Default is zero rotation (should never happen) 
	}
    return tetris::PIECES[m_shapeIndex][x][y]; // Default is zero rotation (should never happen) 
}

char Tetromino::getShape() const{
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

int Tetromino::getX() const{
    return m_x;
}

int Tetromino::getY() const{
    return m_y;
}

tetris::Color Tetromino::getColor() const{
    return tetris::TETROMINO_COLORS[m_shapeIndex];
}

tetris::Color Tetromino::getPreviewColor() const{
	return tetris::PREVIEW_COLORS[m_shapeIndex];
}

void Tetromino::tick(){
    m_y += 1;
}

bool Tetromino::hasBeenHeld() const{
    return m_beenHeld;
}

void Tetromino::hold(){
    reset();
    m_beenHeld = true;
}

void Tetromino::reset(){
    m_x = (tetris::BOARD_WIDTH-tetris::SHAPESIZE)/2;
    m_y = -1;
    m_direction = tetris::DEFAULT_SHAPE_DIRECTION;
}

void Tetromino::move(tetris::Control ch){
    switch (ch) {   
        //Rotate the Tetromino
        case tetris::Control::ROTATE_TETROMINO_KEY:
            rotateRight();
        break;

        //Speed up Tetromino
        //TODO: Change this to a factor(2) that is multiplied when a tick is performed.
        case tetris::Control::MOVE_DOWN_KEY:
            m_y += 1;
        break;

        //Move Tetromino one step to the right
        case tetris::Control::MOVE_RIGHT_KEY:
            m_x += 1;
        break;

        //Move Tetromino one step to the left
        case tetris::Control::MOVE_LEFT_KEY:
            m_x -= 1;
        default:
            //Do not handle all keys here
        break;
     }
}

void Tetromino::draw(bool isPreview) const{
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    const auto color = std::invoke([&](){
        if(isPreview)
            return getPreviewColor();
        else
            return getColor();
    });

    for(int dx = 0; dx < tetris::SHAPESIZE; ++dx){
        for(int dy = 0; dy < tetris::SHAPESIZE; ++dy){
            if(isFilledAt(dx,dy)){
                ScreenHandler::addCharAtBoard('B',(m_x + dx),(m_y + dy), color);
            }
        }
    }
}

void Tetromino::drawAt(int x, int y,bool isPreview){
    //ScreenHandler::moveCurserBoard(screen, m_y, m_x);
    for(int dx = 0; dx < tetris::SHAPESIZE; ++dx){
        for(int dy = 0; dy < tetris::SHAPESIZE; ++dy){
            if(this->isFilledAt(dx,dy)){
                ScreenHandler::addCharAt('B',(x + dx),(y + dy), this->getColor());
            }
        }
    }
}

// Functions

Tetromino testMove(Tetromino bl, tetris::Control ch){
    // Make sure it is a copy of bl
    bl.move(ch);
    return bl;
}

Tetromino testTick(Tetromino bl){
    // Make sure it is a copy of bl
    bl.tick();
    return bl;
}
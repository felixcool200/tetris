#include "shape.h"
#include <stdlib.h>		 /* srand, rand */
#include<iostream>
Shape::Shape(){
	srand(2);
	setShape(rand() % 7);
}

void Shape::setShape(int index){
switch (index){
	case 0:
		m_matrix = O_PIECE;
		break;
	case 1:
		m_matrix = I_PIECE;
		break;
	case 2:
		m_matrix = S_PIECE;
		break;
	case 3:
		m_matrix = Z_PIECE;
		break;
	case 4:
		m_matrix = L_PIECE;
		break;
	case 5:
		m_matrix = J_PIECE;
		break;
	case 6:
		m_matrix = T_PIECE;
		break;
	default:
			break;
	}
}

Shape::Shape(int shapeIndex){
    setShape(shapeIndex);
}

/*
https://stackoverflow.com/questions/37812817/finding-element-at-x-y-in-a-given-matrix-after-rotation-in-c-c
m_dir = 0
		0 1 2 3
		4 5 6 7
		8 9 A B
		C D E F

m_dir = 1
		C 8 4 0
		D 9 5 1
		E A 6 2
		F B 7 3

m_dir = 2
		F E D C
		B A 9 8
		7 6 5 4
		3 2 1 0

m_dir = 3
		3 7 B F
		2 6 A E
		1 5 9 D
		0 4 8 C
*/
bool Shape::getShape(int x, int y){
		if(m_direction == 0){
				return m_matrix[x][y];
		}
		else if(m_direction == 1){
				return m_matrix[y][SHAPESIZE - 1 - x];
		}
		else if(m_direction == 2){
				return m_matrix[SHAPESIZE - 1 - x][SHAPESIZE - 1 - y];
		}
		else{
				return m_matrix[SHAPESIZE - 1 - y][SHAPESIZE - 1 - (SHAPESIZE - 1 - x)];
		}
}

void Shape::rotateRight(){
		m_direction = (m_direction + 1) % 4;
}

void Shape::rotateLeft(){
		m_direction = (m_direction - 1) % 4;
}

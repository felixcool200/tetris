#include "../include/shape.hpp"
#include <stdlib.h>		 /* srand, rand */
#include <iostream>


void Shape::setMatrix(const bool matrix[SHAPESIZE][SHAPESIZE]){
	for(int dy = 0; dy < SHAPESIZE; ++dy){
        for(int dx = 0; dx < SHAPESIZE; ++dx){
            // If there is a block at that position
			m_matrix[dx][dy] = matrix[dx][dy];
        }
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
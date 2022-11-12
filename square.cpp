#include "square.h"

Square::Square(){
	m_board = false;
    m_color = -1;
}

void Square::place(int color){
	m_board = true;
    m_color = color;
}

void Square::remove(){
	m_board = false;
    m_color = -1;
}

bool Square::isPlaced(){
	return m_board;
}

void Square::replace(Square s){
    m_board = s.m_board;
    m_color = s.m_color;
}

int Square::getColor(){
    return m_color;
}
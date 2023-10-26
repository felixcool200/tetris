#include "../include/square.hpp"

Square::Square(){
	m_filled = false;
    m_color = -1;
}

void Square::place(int color){
	m_filled = true;
    m_color = color;
}

void Square::remove(){
	m_filled = false;
    m_color = -1;
}

bool Square::isPlaced(){
	return m_filled;
}

void Square::replace(Square s){
    m_filled = s.m_filled;
    m_color = s.m_color;
}

int Square::getColor(){
    return m_color;
}

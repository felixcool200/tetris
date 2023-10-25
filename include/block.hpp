#pragma once
#include "shape.hpp"
class Block{
    private:
        int m_x;
        int m_y;
        bool m_beenHeld;
        bool m_isPreview;

        Shape m_shape; 
    public:
        Block() : Block((BOARD_WIDTH-SHAPESIZE)/2,-1,false,false){};
        Block(int y) : Block((BOARD_WIDTH-SHAPESIZE)/2,y,false,false){};
        Block(bool held) : Block((BOARD_WIDTH-SHAPESIZE)/2,-1, held,false){};
        Block(bool held, bool isPreview) : Block((BOARD_WIDTH-SHAPESIZE)/2,-1, held, isPreview){};
        Block(int x, int y, bool held, bool isPreview);
        Block(const Block &o);
        
        bool isFilledAt(int x, int y);
        void hold();
        bool hasBeenHeld(); 
        
        void reset();
        void tick();
        void move(int ch);
        void draw();
        void drawAt(int x, int y);
        void rotateRight();
        void update();
        
        int getX();
        int getY();
        int getColor();
        char getShape();

        void setPreview(bool state);

};
Block testMove(Block bl,int ch);
Block testTick(Block bl);

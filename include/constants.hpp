#pragma once

//========== Controls ==========
const char QUIT_KEY = 'q';
const char HOLD_KEY = 'c';
const char TOGGLE_PREVIEW_KEY = 'p';
const char ROTATE_TETROMINO_KEY = 'w';
const char DROP_KEY = ' ';
const char MOVE_LEFT_KEY = 'a';
const char MOVE_RIGHT_KEY = 'd';
const char MOVE_DOWN_KEY = 's';


//========== UI ==========
const int BOARD_WIDTH = 10;
const int BOARD_HEIGHT = 20;
const int START_DELAY_FRAMES = 60;

const int UI_WIDTH = 0;
const int UI_HEIGHT = 0;

const int BORDER_TOP = 1;
const int BORDER_LEFT = 6;
const int BORDER_BOTTOM = 1;
const int BORDER_RIGHT = 11;

//========== DeltaTime ==========
const int microsecondTosecond = 1000000; 
const double secoundsPerFrame = 1.0/120.0;

//========== COLOR ==========
const int COLOR_TETROMINO_BLACK = 0;
const int COLOR_TETROMINO_YELLOW = 1;
const int COLOR_TETROMINO_CYAN = 2;
const int COLOR_TETROMINO_GREEN = 3;
const int COLOR_TETROMINO_RED = 4;
const int COLOR_TETROMINO_WHITE = 5;
const int COLOR_TETROMINO_BLUE = 6;
const int COLOR_TETROMINO_MAGENTA = 7;

const int COLOR_TEXT_BLACK = 8;
const int COLOR_TEXT_YELLOW = 9;
const int COLOR_TEXT_CYAN = 10;
const int COLOR_TEXT_GREEN = 11;
const int COLOR_TEXT_RED = 12;
const int COLOR_TEXT_WHITE = 13;
const int COLOR_TEXT_BLUE = 14;
const int COLOR_TEXT_MAGENTA = 15;

const int COLOR_PREVIEW_YELLOW = 16;
const int COLOR_PREVIEW_CYAN = 17;
const int COLOR_PREVIEW_GREEN = 18;
const int COLOR_PREVIEW_RED = 19;
const int COLOR_PREVIEW_WHITE = 20;
const int COLOR_PREVIEW_BLUE = 21;
const int COLOR_PREVIEW_MAGENTA = 22;

//========== Game logic ========== 
const int MAX_LEVEL = 29;

const int SHAPESIZE = 4;
const int DEFAULT_SHAPE_DIRECTION = 1;

//========== Tetrominos ==========
const int TETROMINOS = 7;
const int TETROMINO_COLORS[TETROMINOS] = {COLOR_TETROMINO_YELLOW, COLOR_TETROMINO_CYAN, COLOR_TETROMINO_GREEN, COLOR_TETROMINO_RED, COLOR_TETROMINO_WHITE, COLOR_TETROMINO_BLUE, COLOR_TETROMINO_MAGENTA};//, COLOR_TETROMINO_BLACK};
const int PREVIEW_COLORS[TETROMINOS] = {COLOR_PREVIEW_YELLOW, COLOR_PREVIEW_CYAN, COLOR_PREVIEW_GREEN, COLOR_PREVIEW_RED, COLOR_PREVIEW_WHITE, COLOR_PREVIEW_BLUE, COLOR_PREVIEW_MAGENTA};//, COLOR_PREVIEW_BLACK};

const bool PIECES[TETROMINOS][SHAPESIZE][SHAPESIZE]{
    // O_PIECE
    {
        {0, 0, 0, 0},
        {0, true, true,0},
        {0, true, true,0},
        {0, 0, 0, 0},
    },
    // I_PIECE
    {
        {0, 0, 0, 0},
        {true, true,true,true},
        {0, 0,0,0},
        {0, 0, 0, 0},
    },
    // S_PIECE
    {
        {0, 0, 0, 0},
        {0, true, true, 0},
        {true, true, 0,0},
        {0, 0, 0, 0},
    },
    // Z_PIECE
    {
        {0, 0, 0, 0},
        {true, true, 0 ,0},
        {0, true, true ,0},
        {0, 0, 0, 0},
    },
    // L_PIECE
    {
        {0, 0, 0, 0},
        {true, true, true,0},
        {true, 0, 0,0},
        {0, 0, 0, 0},
    },
    // J_PIECE
    {
        {0, 0, 0, 0},
        {true, true, true,0},
        {0, 0, true,0},
        {0, 0, 0, 0},
    },
    // T_PIECE
    {
        {0, 0, 0, 0},
        {true,true,true ,0},
        {0, true, 0 ,0},
        {0, 0, 0, 0},
    },
};
/*
const bool O_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {0, true, true,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};

const bool I_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true, true,true,true},
                                            {0, 0,0,0},
                                            {0, 0, 0, 0}};

const bool S_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {0, true, true, 0},
                                            {true, true, 0,0},
                                            {0, 0, 0, 0}};

const bool Z_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true, true, 0 ,0},
                                            {0, true, true ,0},
                                            {0, 0, 0, 0}};

const bool L_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true, true, true,0},
                                            {true, 0, 0,0},
                                            {0, 0, 0, 0}};
const bool J_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true, true, true,0},
                                            {0, 0, true,0},
                                            {0, 0, 0, 0}};

const bool T_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true,true,true ,0},
                                            {0, true, 0 ,0},
                                            {0, 0, 0, 0}};
*/

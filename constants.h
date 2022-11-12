#pragma once

#define BOARD_WIDTH 20
#define BOARD_HEIGHT 20
#define DELAY 20

#define UI_WIDTH 0
#define UI_HEIGHT 0

#define BORDER_TOP 1
#define BORDER_LEFT 1
#define BORDER_BOTTOM 1
#define BORDER_RIGHT 1

#define SHAPESIZE 4

#define COLOR_BLOCK_YELLOW 1
#define COLOR_BLOCK_CYAN 2
#define COLOR_BLOCK_GREEN 3
#define COLOR_BLOCK_RED 4
#define COLOR_BLOCK_WHITE 5
#define COLOR_BLOCK_BLUE 6
#define COLOR_BLOCK_MAGENTA 7
//#define COLOR_BLOCK_BLACK 8

const int BLOCK_COLORS[7] = {COLOR_BLOCK_YELLOW, COLOR_BLOCK_CYAN, COLOR_BLOCK_GREEN, COLOR_BLOCK_RED, COLOR_BLOCK_WHITE, COLOR_BLOCK_BLUE, COLOR_BLOCK_MAGENTA};//, COLOR_BLOCK_BLACK};
const int BLOCKS = 7;
const bool O_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {0, true, true,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};

const bool I_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, 0, 0},
                                            {0, true,0,0},
                                            {0, true,0,0},
                                            {0, true, 0, 0}};

const bool S_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {0, true, true, 0},
                                            {true, true, 0,0},
                                            {0, 0, 0, 0}};

const bool Z_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {true, true, 0 ,0},
                                            {0, true, true ,0},
                                            {0, 0, 0, 0}};

const bool L_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, 0, 0},
                                            {0, true, 0,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};
const bool J_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, true, 0},
                                            {0, 0, true,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};

const bool T_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, 0, 0},
                                            {0, true, 0 ,0},
                                            {true,true,true ,0},
                                            {0, 0, 0, 0}};
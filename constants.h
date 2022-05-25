#pragma once

#define BOARD_WIDTH 10
#define BOARD_HEIGHT 20

#define UI_WIDTH 0
#define UI_HEIGHT 0

#define BORDER_TOP 1
#define BORDER_LEFT 1
#define BORDER_BOTTOM 1
#define BORDER_RIGHT 1

#define SHAPESIZE 4

const bool O_PIECE[SHAPESIZE][SHAPESIZE] = {{true, true, 0, 0},
                                            {true, true, 0,0},
                                            {0, 0, 0, 0},
                                            {0, 0, 0, 0}};

const bool I_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, 0, 0},
                                            {0, true,0,0},
                                            {0, true,0,0},
                                            {0, true, 0, 0}};

const bool S_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, true, 0},
                                            {true, true, 0,0},
                                            {0, 0, 0,0},
                                            {0, 0, 0, 0}};

const bool Z_PIECE[SHAPESIZE][SHAPESIZE] = {{true, true, 0, 0},
                                            {0, true, true ,0},
                                            {0, 0, 0 ,0},
                                            {0, 0, 0, 0}};

const bool L_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, 0, 0},
                                            {0, true, 0,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};

const bool J_PIECE[SHAPESIZE][SHAPESIZE] = {{0, 0, true, 0},
                                            {0, 0, true,0},
                                            {0, true, true,0},
                                            {0, 0, 0, 0}};

const bool T_PIECE[SHAPESIZE][SHAPESIZE] = {{0, true, 0, 0},
                                            {true,true,true ,0},
                                            {0, 0, 0 ,0},
                                            {0, 0, 0, 0}};
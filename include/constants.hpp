#pragma once
//========== Controls ==========
const char QUIT_KEY = 'q';
const char HOLD_KEY = 'c';
const char TOGGLE_PREVIEW_KEY = 'p';
const char ROTATE_BLOCK_KEY = 'w';
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
const int BORDER_RIGHT = 10;

//========== Game logic ========== 
const int MAX_LEVEL = 29;

const int SHAPESIZE = 4;
const int DEFAULT_SHAPE_DIRECTION = 1;

//========== DeltaTime ==========
const int microsecondTosecond = 1000000; 
const double secoundsPerFrame = 1.0/60.0;

//========== COLOR ==========
const int COLOR_BLOCK_YELLOW = 1;
const int COLOR_BLOCK_CYAN = 2;
const int COLOR_BLOCK_GREEN = 3;
const int COLOR_BLOCK_RED = 4;
const int COLOR_BLOCK_WHITE = 5;
const int COLOR_BLOCK_BLUE = 6;
const int COLOR_BLOCK_MAGENTA = 7;
const int COLOR_BLOCK_BLACK = 8;

//========== BLOCKS ==========
const int BLOCKS = 7;
const int BLOCK_COLORS[BLOCKS] = {COLOR_BLOCK_YELLOW, COLOR_BLOCK_CYAN, COLOR_BLOCK_GREEN, COLOR_BLOCK_RED, COLOR_BLOCK_WHITE, COLOR_BLOCK_BLUE, COLOR_BLOCK_MAGENTA};//, COLOR_BLOCK_BLACK};

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

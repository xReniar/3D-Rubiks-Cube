#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Direction {
    CLOCKWISE,
    ANTICLOCKWISE
};

enum _Side_ {
    TOP_SIDE,
    BOTTOM_SIDE,
    FRONT_SIDE,
    RIGHT_SIDE,
    BACK_SIDE,
    LEFT_SIDE
};

enum Color { 
    YELLOW,
    WHITE,
    BLUE,
    RED,
    GREEN,
    ORANGE,
    BLACK
};

enum Solve_State {
    CROSS,
    F2L,
    OLL,
    PLL
};

#endif
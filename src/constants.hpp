#ifndef CONSTANTS_H
#define CONSTANTS_H

enum Direction {
    CLOCKWISE,
    ANTICLOCKWISE
};

enum _Side_ {
    TOP_SIDE='U',
    BOTTOM_SIDE='D',
    FRONT_SIDE='F',
    RIGHT_SIDE='R',
    BACK_SIDE='B',
    LEFT_SIDE='L'
};

enum LayerType {
    INNER,
    OUTER
};

enum Color {
    YELLOW='U',
    WHITE='D',
    BLUE='F',
    RED='R',
    GREEN='B',
    ORANGE='L'
};

#endif
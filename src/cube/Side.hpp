#ifndef SIDE_H
#define SIDE_H

#include"../constants.hpp"

class Side {
public:
    Color slot[9];
    Side(Color color);
    Side(Color colors[]);
    void turn(Direction direction);
};

#endif
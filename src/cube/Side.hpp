#ifndef SIDE_H
#define SIDE_H

#include"../constants.hpp"
#include<vector>

struct Cubie {
    int id;
    Color color;
};

class Side {
public:
    Cubie slot[9];
    Side(Color color, std::vector<int> pieceId);
    Side(Color colors[], std::vector<int> pieceId);
    void turn(Direction direction);
};

#endif
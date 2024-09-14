#ifndef SIDE_H
#define SIDE_H

#include"../constants.hpp"
#include<vector>

struct Cubie {
    int id;
    Color color;
};

class Side {
private:
    int size;
    std::vector<int> index;
public:
    Cubie* cubie;
    Side(int size, Color color, std::vector<int> pieceId);
    ~Side();
    void turn(Direction direction);
};

#endif
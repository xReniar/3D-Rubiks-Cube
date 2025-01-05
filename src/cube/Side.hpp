#ifndef SIDE_H
#define SIDE_H

#include "../constants.hpp"
#include <vector>
#include <functional>

class Cubie
{
public:
    int id;
    Color color;


    char getLetter()
    {
        return static_cast<char>(this->color);
    }
};

class Side
{
private:
    int size;
    std::vector<int> index;
    std::function<void(Direction)> turnFunction;
public:
    _Side_ sidename;
    Cubie *cubie;
    Side(_Side_ sidename, int size, Color color, std::vector<int> pieceId,std::function<void(Direction)> turnFunction);
    ~Side();
    void turn(Direction direction);
};

#endif
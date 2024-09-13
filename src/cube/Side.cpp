#include"Side.hpp"

Side::Side(int size, Color color, std::vector<int> pieceId) : size(size){
    cubie = new Cubie[this->size];
    for(int i = 0;i < this->size;i++){
        cubie[i].color = color;
        cubie[i].id = pieceId[i];
    }
}

Side::~Side(){
    delete[] cubie;
}

void Side::turn(Direction Direction){
    /* make a copy */
    Cubie _copy[size];
    for(int i = 0;i < size;i++){
        _copy[i] = cubie[i];
    }

    /* turn clockwise or anticlockwise */
    if(Direction == CLOCKWISE){
        cubie[0] = _copy[6];
        cubie[1] = _copy[3];
        cubie[2] = _copy[0];
        cubie[3] = _copy[7];
        cubie[4] = _copy[4];
        cubie[5] = _copy[1];
        cubie[6] = _copy[8];
        cubie[7] = _copy[5];
        cubie[8] = _copy[2];
    }
    if(Direction == ANTICLOCKWISE){
        cubie[0] = _copy[2];
        cubie[1] = _copy[5];
        cubie[2] = _copy[8];
        cubie[3] = _copy[1];
        cubie[4] = _copy[4];
        cubie[5] = _copy[7];
        cubie[6] = _copy[0];
        cubie[7] = _copy[3];
        cubie[8] = _copy[6];
    }
}
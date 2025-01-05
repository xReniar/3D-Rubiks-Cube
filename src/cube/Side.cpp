#include"Side.hpp"
#include<iostream>

Side::Side(_Side_ sidename, int size, Color color, std::vector<int> pieceId, std::function<void(Direction)> turnFunction) : size(size){
    this->turnFunction = turnFunction;
    this->sidename = sidename;
    cubie = new Cubie[this->size * this->size];
    for(int i = 0;i < this->size * this->size;i++){
        cubie[i].color = color;
        cubie[i].id = pieceId[i];
    }

    // calculating index for face turn
    int currIndex = 0;
    for(int i = this->size - 1;i > -1;i--){
        currIndex = i;
        for(int j = 0; j < this->size;j++){
            index.push_back(currIndex);
            currIndex += this->size;
        }
    }
}

Side::~Side(){
    delete[] cubie;
}

void Side::turn(Direction Direction){
    /* make a copy */
    int numOfPieces = size * size;
    std::vector<Cubie> _copy(numOfPieces);
    for(int i = 0;i < numOfPieces;i++){
        _copy[i] = cubie[i];
    }

    /* turn clockwise or anticlockwise */
    if(Direction == CLOCKWISE){
        for(int i = 0;i < numOfPieces;i++){
            cubie[i] = _copy[index[numOfPieces - 1 - i]];
        }
    }
    if(Direction == ANTICLOCKWISE){
        for(int i = 0;i < numOfPieces;i++){
            cubie[i] = _copy[index[i]];
        }
    }
    this->turnFunction(Direction);
}
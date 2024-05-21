#include"Side.hpp"

Side::Side(Color color){
    for(int i = 0;i < 9;i++){
        slot[i] = color;
    }
}

Side::Side(Color colors[]){
    for(int i = 0;i < 9;i++){
        slot[i] = colors[i];
    }
}

void Side::turn(Direction Direction){
    /* make a copy */
    Color _copy[9];
    for(int i = 0;i < 9;i++){
        _copy[i] = slot[i];
    }

    /* turn clockwise or anticlockwise */
    if(Direction == CLOCKWISE){
        slot[0] = _copy[6];
        slot[1] = _copy[3];
        slot[2] = _copy[0];
        slot[3] = _copy[7];
        slot[4] = _copy[4];
        slot[5] = _copy[1];
        slot[6] = _copy[8];
        slot[7] = _copy[5];
        slot[8] = _copy[2];
    }
    if(Direction == ANTICLOCKWISE){
        slot[0] = _copy[2];
        slot[1] = _copy[5];
        slot[2] = _copy[8];
        slot[3] = _copy[1];
        slot[4] = _copy[4];
        slot[5] = _copy[7];
        slot[6] = _copy[0];
        slot[7] = _copy[3];
        slot[8] = _copy[6];
    }
}
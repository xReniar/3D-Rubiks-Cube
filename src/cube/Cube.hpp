#ifndef CUBE_H
#define CUBE_H

#include"Side.hpp"
#include<string>

class Cube {
private:
    Side top_side;
    Side bottom_side;
    Side front_side;
    Side right_side;
    Side back_side;
    Side left_side;
    void u_turn(Direction direction);
    void d_turn(Direction direction);
    void f_turn(Direction direction);
    void r_turn(Direction direction);
    void b_turn(Direction direction);
    void l_turn(Direction direction);
    void rotate(_Side_ side,Direction direction);
public:
    Cube();
    void turn(const std::string& str);
    void show();
};

#endif
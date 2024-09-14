#ifndef CUBE3_H
#define CUBE3_H

#include"Side.hpp"
#include<string>
#include<vector>
#include<iostream>

class Cube3 {
private:
    Side* top_side;
    Side* bottom_side;
    Side* front_side;
    Side* right_side;
    Side* back_side;
    Side* left_side;

    void u_turn(Direction direction);
    void d_turn(Direction direction);
    void f_turn(Direction direction);
    void r_turn(Direction direction);
    void b_turn(Direction direction);
    void l_turn(Direction direction);
    void rotate(_Side_ side,Direction direction);

    char f(Cubie cubie);
public:
    Cube3();
    void turn(const std::string& str);
    std::string state();
    bool isSolved();
    std::vector<int> getFaceId(std::string side);
};

#endif
#ifndef SOLVER_H
#define SOLVER_H

#include"../cube/Cube.hpp"

class Solver {
public:
    std::string solution;
    void kociemba(const char* cubeState);
};

#endif
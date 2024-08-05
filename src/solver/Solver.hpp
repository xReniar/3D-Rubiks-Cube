#ifndef SOLVER_H
#define SOLVER_H

#include"../cube/Cube.hpp"

class Solver {
public:
    Solver();
    std::string getSolution(std::string cubeState);
};

#endif
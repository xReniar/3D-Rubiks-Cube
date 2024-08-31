#ifndef SOLVER_H
#define SOLVER_H

#include"../cube/Cube.hpp"
#include<python3.10/Python.h>
#include<sstream>

class Solver {
public:
    Solver();
    ~Solver();
    std::vector<std::string> solution;
    bool solutionReady = false;
    PyObject *name, *load_module, *func, *callfunc, *args;

    void freeMemory();
    void kociemba(const char* cubeState);
};

#endif
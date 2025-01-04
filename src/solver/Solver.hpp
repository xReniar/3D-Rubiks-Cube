#ifndef SOLVER_H
#define SOLVER_H

#include<iostream>
#include<vector>
#include<string>
#include<sstream>

class Solver {
public:
    std::vector<std::string> solution;
    bool solutionReady = false;

    void kociemba(const char* cubeState);
};

#endif
#include "Solver.hpp"
#include <iostream>

extern "C"
{
    char* solve_cube(int argc, char **argv);
}

void Solver::kociemba(const char *cubeState)
{
    std::cout << "[SOLVER] - calculating solution" << std::endl;
    const char* args[] = {"program_name", cubeState};
    int argc = sizeof(args) / sizeof(args[0]);
    char** argv = const_cast<char**>(args);
    char* result = solve_cube(argc, argv);

    std::cout << "[SOLVER] - solution found: " << result << std::endl;

    std::stringstream stringStream(result);
    std::string word;

    while (stringStream >> word)
        solution.push_back(word);
    solutionReady = true;

}
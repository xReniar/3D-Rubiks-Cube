#include"src/Rubiks.hpp"

int main(){
    Cube cube;
    Solver solver;

    CubeGUI gui;

    try {
        gui.run();
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

    //solver.solve(cube);

    //cube.turn("UDFRBL");
    return 0;
}
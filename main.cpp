#include"src/Rubiks.hpp"

int main(){
    Cube cube;
    Solver solver;

    CubeApp app{};

    try {
        app.run();
    } catch(const std::exception &error) {
        std::cerr << error.what() << "\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
    //solver.solve(cube);

    //cube.turn("UDFRBL");
}
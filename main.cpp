#include"src/Rubiks.hpp"

int main(){
    Cube cube;
    Solver solver;

    solver.solve(cube);

    cube.turn("UDFRBL");

    /*
    for(int i = 0;i < 1;i++){
        cube.turn("R2L2F2B2U2D2");
        //cube.show();
    }
    */
    cube.show();
    return 0;
}
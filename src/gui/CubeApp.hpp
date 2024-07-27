#ifndef CUBEAPP_H
#define CUBEAPP_H

#include"CubeGUI.hpp"

class CubeApp {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();
private:
    CubeGUI cubeGUI{WIDTH, HEIGHT, "Vulkan Rubik's Cube"};
};


#endif
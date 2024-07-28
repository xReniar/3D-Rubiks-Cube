#ifndef CUBEAPP_H
#define CUBEAPP_H

#include"cube_gui.hpp"
#include"pipeline.hpp"
#include"device.hpp"

class CubeApp {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    void run();
private:
    CubeGUI cubeGUI{WIDTH, HEIGHT, "Vulkan Rubik's Cube"};
    Device device{cubeGUI};
    Pipeline pipeline{
        device,
        "shaders/shader.vert.spv",
        "shaders/shader.frag.spv",
        Pipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
};


#endif
#ifndef CUBEAPP_H
#define CUBEAPP_H

#include"cube_gui.hpp"
#include"device.hpp"
#include"cube_obj.hpp"
#include"renderer.hpp"

#include<memory>
#include<vector>

class CubeApp {
public:
    static constexpr int WIDTH = 800;
    static constexpr int HEIGHT = 600;

    CubeApp();
    ~CubeApp();

    CubeApp(const CubeApp &) = delete;
    CubeApp &operator=(const CubeApp &) = delete;

    void run();
private:
    CubeGUI cubeGUI{WIDTH, HEIGHT, "Vulkan Rubik's Cube"};
    Device device{cubeGUI};
    Renderer renderer{cubeGUI, device};
    std::vector<CubeObj> gameObjects;

    void createCenters();
    void createEdges();
    void createCorners();
    void loadGameObjects();

};


#endif
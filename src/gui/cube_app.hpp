#ifndef CUBEAPP_H
#define CUBEAPP_H

#include"cube_gui.hpp"
#include"pipeline.hpp"
#include"swap_chain.hpp"
#include"device.hpp"
#include"model.hpp"

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
    SwapChain swapChain{ device, cubeGUI.getExtent() };
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;
    std::vector<VkCommandBuffer> commandBuffers;
    std::unique_ptr<Model> model;

    void createPipelineLayout();
    void createPipeline();
    void createCommandBuffers();
    void drawFrame();
    void loadModels();
};


#endif
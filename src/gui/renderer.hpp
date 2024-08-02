#ifndef RENDERER_H
#define RENDERER_H

#include"cube_gui.hpp"
#include"swap_chain.hpp"
#include"device.hpp"
#include"model.hpp"

#include<memory>
#include<vector>
#include<cassert>

class Renderer {
public:
    Renderer(CubeGUI &cubeGUI, Device &device);
    ~Renderer();

    Renderer(const Renderer &) = delete;
    Renderer &operator=(const Renderer &) = delete;

    VkRenderPass getSwapChainRenderPass() const { return swapChain->getRenderPass(); }
    float getAspectRatio() const { return swapChain->extentAspectRatio(); }
    bool isFrameInProgress() const { return isFrameStarted; }
    VkCommandBuffer getCurrentCommandBuffer() const {
        assert(isFrameStarted && "Cannot get command buffer when frame not in progress");
        return commandBuffers[currentFrameIndex]; 
    }

    int getFrameIndex() const {
        assert(isFrameStarted && "Cannot get frame index when frame not in progress");
        return currentFrameIndex;
    }

    VkCommandBuffer beginFrame();
    void endFrame();
    void beginSwapChainRenderPass(VkCommandBuffer commandBuffer);
    void endSwapChainRenderPass(VkCommandBuffer commandBuffer);
private:
    CubeGUI &cubeGUI;
    Device &device;
    std::unique_ptr<SwapChain> swapChain;
    std::vector<VkCommandBuffer> commandBuffers;
    uint32_t currentImageIndex = 0;
    int currentFrameIndex;
    bool isFrameStarted = false;

    void createCommandBuffers();
    void recreateSwapChain();
    void freeCommandBuffers();

};

#endif
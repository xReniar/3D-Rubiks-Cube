#ifndef RENDER_SYSTEM_H
#define RENDER_SYSTEM_H

#include"pipeline.hpp"
#include"device.hpp"
#include"cube_obj.hpp"
#include"camera.hpp"

#include<memory>
#include<vector>

class RenderSystem {
public:
    RenderSystem(Device &device, VkRenderPass renderPass);
    ~RenderSystem();

    RenderSystem(const RenderSystem &) = delete;
    RenderSystem &operator=(const RenderSystem &) = delete;

    void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<CubeObj> &gameObjects, const Camera& camera);
    unsigned getMaxFrameRate();
private:
    Device &device;
    std::unique_ptr<Pipeline> pipeline;
    VkPipelineLayout pipelineLayout;

    void createPipelineLayout();
    void createPipeline(VkRenderPass renderPass);

};

#endif
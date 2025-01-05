#include"render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>

#include<cassert>
#include<stdexcept>
#include<array>

struct SimplePushCostantData {
    glm::mat4 transform{1.f};
    alignas(16) glm::vec3 color;
};

RenderSystem::RenderSystem(Device &device, VkRenderPass renderPass): device{device}{
    createPipelineLayout();
    createPipeline(renderPass);
}

RenderSystem::~RenderSystem(){
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

// Function to query the maximum frame rate
unsigned RenderSystem::getMaxFrameRate() {
    return 75; // Default to 75 FPS for VK_PRESENT_MODE_FIFO_KHR
}

void RenderSystem::createPipelineLayout(){
    VkPushConstantRange pushConstantRange{};
    pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
    pushConstantRange.offset = 0;
    pushConstantRange.size = sizeof(SimplePushCostantData);

    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 1;
    pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange;

    if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        throw std::runtime_error("failed to create pipeline layout!");
}

void RenderSystem::createPipeline(VkRenderPass renderPass){
    assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");

    PipelineConfigInfo pipelineConfig{};
    PipelineConfigInfo::defaultPipelineConfigInfo(pipelineConfig);
    pipelineConfig.renderPass = renderPass;
    pipelineConfig.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(
        device,
        "shaders/shader.vert.spv",
        "shaders/shader.frag.spv",
        pipelineConfig
    );
}

void RenderSystem::renderGameObjects(VkCommandBuffer commandBuffer, std::vector<CubeObj> &gameObjects, const Camera& camera){
    pipeline->bind(commandBuffer);

    auto projectionView = camera.getProjection() * camera.getView();

    for(auto& obj: gameObjects){
        SimplePushCostantData push{};
        push.transform = projectionView * obj.transform.mat4();
        push.color = obj.color;

        vkCmdPushConstants(
            commandBuffer,
            pipelineLayout,
            VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
            0,
            sizeof(SimplePushCostantData),
            &push
        );

        obj.model->bind(commandBuffer);
        obj.model->draw(commandBuffer);
    }
}
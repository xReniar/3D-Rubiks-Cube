#include"cube_app.hpp"

#include<stdexcept>

CubeApp::CubeApp(){
    createPipelineLayout();
    createPipeline();
    createCommandBuffers();
}

CubeApp::~CubeApp(){
    vkDestroyPipelineLayout(device.device(), pipelineLayout, nullptr);
}

void CubeApp::run(){
    while(!cubeGUI.shouldClose()){
        glfwPollEvents();
    }
}

void CubeApp::createPipelineLayout(){
    VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
    pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    pipelineLayoutInfo.setLayoutCount = 0;
    pipelineLayoutInfo.pSetLayouts = nullptr;
    pipelineLayoutInfo.pushConstantRangeCount = 0;
    pipelineLayoutInfo.pPushConstantRanges = nullptr;

    if(vkCreatePipelineLayout(device.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        throw std::runtime_error("failed to create pipeline layout!");
}

void CubeApp::createPipeline(){
    auto pipelineConfig = Pipeline::defaultPipelineConfigInfo(swapChain.width(), swapChain.height());
    pipelineConfig.renderPass = swapChain.getRenderPass();
    pipelineConfig.pipelineLayout = pipelineLayout;
    pipeline = std::make_unique<Pipeline>(
        device,
        "shaders/shader.vert.spv",
        "shaders/shader.frag.spv",
        pipelineConfig
    );
}

void CubeApp::createCommandBuffers(){

}

void CubeApp::drawFrame(){

}
#include"cube_app.hpp"

#include"render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>

#include<cassert>
#include<stdexcept>
#include<array>


CubeApp::CubeApp(){
    loadGameObjects();
}

CubeApp::~CubeApp(){}

void CubeApp::run(){
    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    while(!cubeGUI.shouldClose()){
        glfwPollEvents();
        if(auto commandBuffer = renderer.beginFrame()){
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

void CubeApp::loadGameObjects(){
    std::vector<Model::Vertex> vertices {
        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f }},
        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
    };

    auto model = std::make_shared<Model>(device, vertices);
    auto triangle = CubeObj::createGameObject();
    triangle.model = model;
    triangle.color = { .1f, .8f, .1f };
    triangle.transform2d.translation.x = .2f;
    triangle.transform2d.scale = {2.f, .5f};
    triangle.transform2d.rotation = .25f * glm::two_pi<float>();

    gameObjects.push_back(std::move(triangle));
}
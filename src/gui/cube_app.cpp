#include"cube_app.hpp"

#include"controller.hpp"
#include"render_system.hpp"
#include"camera.hpp"
#include"../constants.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/glm.hpp>
#include<glm/gtc/constants.hpp>

#include<cassert>
#include<stdexcept>
#include<array>
#include<chrono>


CubeApp::CubeApp(){
    loadGameObjects();
}

CubeApp::~CubeApp(){}

void CubeApp::run(){
    RenderSystem renderSystem{device, renderer.getSwapChainRenderPass()};
    Camera camera{};
    //camera.setViewDirection(glm::vec3(0.f), glm::vec3(0.5f, 0.f, 1.f));
    camera.setViewTarget(glm::vec3(-1.f, -2.f, 2.f), glm::vec3(0.f, 0.f, 2.5f));

    auto viewerObject = CubeObj::createGameObject();
    Controller cameraController{};

    auto currentTime = std::chrono::high_resolution_clock::now();

    while(!cubeGUI.shouldClose()){
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        cameraController.moveInPlaneXZ(cubeGUI.getGLFWwindow(), frameTime, viewerObject);
        camera.setViewYXZ(viewerObject.transform.translation, viewerObject.transform.rotation);

        float aspect = renderer.getAspectRatio();
        //camera.setOrthographicProjection(-aspect, aspect,-1, 1, -1, 1);
        camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);

        if(auto commandBuffer = renderer.beginFrame()){
            renderer.beginSwapChainRenderPass(commandBuffer);
            renderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
            renderer.endSwapChainRenderPass(commandBuffer);
            renderer.endFrame();
        }
    }

    vkDeviceWaitIdle(device.device());
}

std::unique_ptr<Model> createCubeModel(Device& device, glm::vec3 offset,const std::vector<glm::vec3> &colors) {
    std::vector<Model::Vertex> vertices{
        // top face (yellow)
        {{-.5f, -.5f, -.5f}, colors[0]},
        {{.5f, -.5f, .5f}, colors[0]},
        {{-.5f, -.5f, .5f}, colors[0]},
        {{-.5f, -.5f, -.5f}, colors[0]},
        {{.5f, -.5f, -.5f}, colors[0]},
        {{.5f, -.5f, .5f}, colors[0]},
    
        // bottom face (white)
        {{-.5f, .5f, -.5f}, colors[1]},
        {{.5f, .5f, .5f}, colors[1]},
        {{-.5f, .5f, .5f}, colors[1]},
        {{-.5f, .5f, -.5f}, colors[1]},
        {{.5f, .5f, -.5f}, colors[1]},
        {{.5f, .5f, .5f}, colors[1]},

        // back face (blue)
        {{-.5f, -.5f, -0.5f}, colors[2]},
        {{.5f, .5f, -0.5f}, colors[2]},
        {{-.5f, .5f, -0.5f}, colors[2]},
        {{-.5f, -.5f, -0.5f}, colors[2]},
        {{.5f, -.5f, -0.5f}, colors[2]},
        {{.5f, .5f, -0.5f}, colors[2]},
    
        // right face (red)
        {{.5f, -.5f, -.5f}, colors[3]},
        {{.5f, .5f, .5f}, colors[3]},
        {{.5f, -.5f, .5f}, colors[3]},
        {{.5f, -.5f, -.5f}, colors[3]},
        {{.5f, .5f, -.5f}, colors[3]},
        {{.5f, .5f, .5f}, colors[3]},

        // front face (green)
        {{-.5f, -.5f, 0.5f}, colors[4]},
        {{.5f, .5f, 0.5f}, colors[4]},
        {{-.5f, .5f, 0.5f}, colors[4]},
        {{-.5f, -.5f, 0.5f}, colors[4]},
        {{.5f, -.5f, 0.5f}, colors[4]},
        {{.5f, .5f, 0.5f}, colors[4]},
    
        // left face (orange)
        {{-.5f, -.5f, -.5f}, colors[5]},
        {{-.5f, .5f, .5f}, colors[5]},
        {{-.5f, -.5f, .5f}, colors[5]},
        {{-.5f, -.5f, -.5f}, colors[5]},
        {{-.5f, .5f, -.5f}, colors[5]},
        {{-.5f, .5f, .5f}, colors[5]},
    };
    for (auto& v : vertices)
        v.position += offset;
    return std::make_unique<Model>(device, vertices);
}

std::vector<glm::vec3> Vec3Color(const std::vector<Color>& colors){
    std::vector<glm::vec3> vec3Colors(colors.size());
    
    glm::vec3 currentColor;
    for(size_t i = 0;i < vec3Colors.size(); i++){
        if(colors[i] == YELLOW) currentColor = {.8f, .8f, .1f};
        if(colors[i] == WHITE) currentColor = {.9f, .9f, .9f};
        if(colors[i] == BLUE) currentColor = {.1f, .1f, .8f};
        if(colors[i] == RED) currentColor = {.8f, .1f, .1f};
        if(colors[i] == GREEN) currentColor = {.1f, .8f, .1f};
        if(colors[i] == ORANGE) currentColor = {.9f, .6f, .1f};
        if(colors[i] == BLACK) currentColor = {.0f, .0f, .0f };
        
        vec3Colors[i] = currentColor;
    }
    return vec3Colors;
}

void CubeApp::createCenters(){
    std::vector<std::vector<Color>> colors = {
        {YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK}, 
        {BLACK, WHITE, BLACK, BLACK, BLACK, BLACK},
        {BLACK, BLACK, BLUE, BLACK, BLACK, BLACK},
        {BLACK, BLACK, BLACK, RED, BLACK, BLACK},
        {BLACK, BLACK, BLACK, BLACK, GREEN, BLACK},
        {BLACK, BLACK, BLACK, BLACK, BLACK, ORANGE}
    };

    std::vector<glm::vec3> offsets = {
        { .0f, -1.0f, .0f },
        { .0f, 1.0f, .0f },
        { .0f, .0f, -1.0f },
        { 1.0f, .0f, .0f },
        { .0f, .0f, 1.0f },
        { -1.0f, .0f, .0f }
    };

    assert(colors.size() == offsets.size());

    for(int i = 0;i < colors.size();i++){
        std::shared_ptr<Model> fixCenter = createCubeModel(device, offsets[i], Vec3Color(colors[i]));
        auto center = CubeObj::createGameObject();
        center.model = fixCenter;
        center.transform.translation = { .0f, .0f, 2.5f };
        center.transform.scale = { .25f, .25f, .25f };

        gameObjects.push_back(std::move(center));
    }
}

void CubeApp::createEdges(){
    std::vector<std::vector<Color>> colors = {
        {YELLOW, BLACK, BLUE, BLACK, BLACK, BLACK},
        {YELLOW, BLACK, BLACK, RED, BLACK, BLACK},
        {YELLOW, BLACK, BLACK, BLACK, GREEN, BLACK},
        {YELLOW, BLACK, BLACK, BLACK, BLACK, ORANGE},
        {BLACK, BLACK, BLUE, RED, BLACK, BLACK},
        {BLACK, BLACK, BLACK, RED, GREEN, BLACK}
    };

    std::vector<glm::vec3> offsets = {
        { .0f, -1.0f, -1.0f },
        { 1.0f, -1.0f, .0f },
        { .0f, -1.0f, 1.0f },
        { -1.0f, -1.0f, .0f },
        { 1.0f, .0f , -1.0f },
        { 1.0f, .0f , 1.0f }
    };

    assert(colors.size() == offsets.size());

    for(int i = 0;i < colors.size();i++){
        std::shared_ptr<Model> edge = createCubeModel(device, offsets[i], Vec3Color(colors[i]));
        auto edgeObj = CubeObj::createGameObject();
        edgeObj.model = edge;
        edgeObj.transform.translation = { .0f, .0f, 2.5f };
        edgeObj.transform.scale = { .25f, .25f, .25f };

        gameObjects.push_back(std::move(edgeObj));
    }
}

void CubeApp::createCorners(){

}

void CubeApp::loadGameObjects(){
    /*
    std::shared_ptr<Model> edge = createCubeModel(device, { .0f, .0f, .0f }, Vec3Color({YELLOW, WHITE, BLUE, RED, GREEN, ORANGE}));
    auto edgeObj = CubeObj::createGameObject();
    edgeObj.model = edge;
    edgeObj.transform.translation = { .0f, .0f, 2.5f };
    edgeObj.transform.scale = { .25f, .25f, .25f };

    gameObjects.push_back(std::move(edgeObj));
    */
    createCenters();
    createEdges();
    createCorners();
}
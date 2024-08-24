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
    viewerObject.transform.translation.z = -4.5f;
    Controller controller{};

    GLFWwindow* window = cubeGUI.getGLFWwindow();

    auto currentTime = std::chrono::high_resolution_clock::now();

    while(!cubeGUI.shouldClose()){
        glfwPollEvents();

        auto newTime = std::chrono::high_resolution_clock::now();
        float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(newTime - currentTime).count();
        currentTime = newTime;

        controller.orbitAroundCube(window, frameTime, viewerObject);
        controller.rotateCube(window, frameTime, gameObjects);
        controller.solveCube(window, frameTime, gameObjects);

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

void CubeApp::loadGameObjects(){
    // defining translation
    std::vector<glm::vec3> translation{};
    for(int i = -1;i <= 1;i++)
        for(int j = -1;j <= 1;j++)
            for(int k = -1;k <= 1;k++)
                if(!(i == 0 && j == 0 && k == 0))
                    translation.push_back(glm::vec3(((float) i)/2,((float) j)/2,((float) k)/2));

    std::vector<std::string> models = {
        "models/new_blender/corner_yellowOrangeBlue.obj",    // 0
        "models/new_blender/edge_yellowOrange.obj",          // 1
        "models/new_blender/corner_yellowGreenOrange.obj",   // 2
        "models/new_blender/edge_OrangeBlue.obj",            // 3
        "models/new_blender/center_orange.obj",              // 4
        "models/new_blender/edge_GreenOrange.obj",           // 5
        "models/new_blender/corner_whiteOrangeBlue.obj",     // 6
        "models/new_blender/edge_whiteOrange.obj",           // 7
        "models/new_blender/corner_whiteGreenOrange.obj",    // 8
        "models/new_blender/edge_yellowBlue.obj",            // 9
        "models/new_blender/center_yellow.obj",              // 10
        "models/new_blender/edge_yellowGreen.obj",           // 11
        "models/new_blender/center_blue.obj",                // 12
        "models/new_blender/center_green.obj",               // 13
        "models/new_blender/edge_whiteBlue.obj",             // 14
        "models/new_blender/center_white.obj",               // 15
        "models/new_blender/edge_whiteGreen.obj",            // 16
        "models/new_blender/corner_yellowBlueRed.obj",       // 17
        "models/new_blender/edge_yellowRed.obj",             // 18
        "models/new_blender/corner_yellowRedGreen.obj",      // 19
        "models/new_blender/edge_BlueRed.obj",               // 20
        "models/new_blender/center_red.obj",                 // 21
        "models/new_blender/edge_RedGreen.obj",              // 22
        "models/new_blender/corner_whiteBlueRed.obj",        // 23
        "models/new_blender/edge_whiteRed.obj",              // 24
        "models/new_blender/corner_whiteRedGreen.obj"        // 25
    };

    for(int i = 0;i < models.size(); i++){
        std::shared_ptr<Model> model = Model::createModelFromFile(device, models[i]);
        auto cube = CubeObj::createGameObject();
        cube.model = model;
        cube.transform.translation = translation[i];
        cube.transform.scale = { .5f, .5f, .5f };

        gameObjects.push_back(std::move(cube));
    }
}

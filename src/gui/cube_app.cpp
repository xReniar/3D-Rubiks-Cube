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
    std::vector<std::string> models = {
        /*
        "models/center_yellow.obj",                 // 0
        "models/center_white.obj",                  // 1
        "models/center_blue.obj",                   // 2
        "models/center_red.obj",                    // 3
        "models/center_green.obj",                  // 4
        "models/center_orange.obj",                 // 5
        "models/edge_yellowBlue.obj",               // 6
        "models/edge_yellowRed.obj",                // 7
        "models/edge_yellowGreen.obj",              // 8
        "models/edge_yellowOrange.obj",             // 9
        "models/edge_whiteBlue.obj",                // 10
        "models/edge_whiteRed.obj",                 // 11
        "models/edge_whiteGreen.obj",               // 12
        "models/edge_whiteOrange.obj",              // 13
        "models/edge_blueRed.obj",                  // 14
        "models/edge_redGreen.obj",                 // 15
        "models/edge_greenOrange.obj",              // 16
        "models/edge_orangeBlue.obj",               // 17
        "models/corner_whiteBlueRed.obj",           // 18
        "models/corner_whiteRedGreen.obj",          // 19
        "models/corner_whiteGreenOrange.obj",       // 20
        "models/corner_whiteOrangeBlue.obj",        // 21
        "models/corner_yellowBlueRed.obj",          // 22
        "models/corner_yellowRedGreen.obj",         // 23
        "models/corner_yellowGreenOrange.obj",      // 24
        "models/corner_yellowOrangeBlue.obj"        // 25
        */
        "models/blender/center_yellow.obj",
        "models/blender/center_white.obj",
        "models/blender/center_blue.obj",
        "models/blender/center_red.obj",
        "models/blender/center_green.obj",
        "models/blender/center_orange.obj",
        "models/blender/edge_yellowBlue.obj",
        "models/blender/edge_yellowRed.obj",
        "models/blender/edge_yellowGreen.obj",
        "models/blender/edge_yellowOrange.obj",
        "models/blender/edge_whiteBlue.obj",
        "models/blender/edge_whiteRed.obj",
        "models/blender/edge_whiteGreen.obj",
        "models/blender/edge_whiteOrange.obj",
        "models/blender/edge_BlueRed.obj",
        "models/blender/edge_RedGreen.obj",
        "models/blender/edge_GreenOrange.obj",
        "models/blender/edge_OrangeBlue.obj",
        "models/blender/corner_whiteBlueRed.obj",
        "models/blender/corner_whiteRedGreen.obj",
        "models/blender/corner_whiteGreenOrange.obj",
        "models/blender/corner_whiteOrangeBlue.obj",
        "models/blender/corner_yellowBlueRed.obj",
        "models/blender/corner_yellowRedGreen.obj",
        "models/blender/corner_yellowGreenOrange.obj",
        "models/blender/corner_yellowOrangeBlue.obj"
    };

    for(auto modelName : models){
        std::shared_ptr<Model> model = Model::createModelFromFile(device, modelName);
        auto cube = CubeObj::createGameObject();
        cube.model = model;
        cube.transform.translation = { .0f, .0f, 2.5f };
        cube.transform.scale = { .25f, .25f, .25f };

        gameObjects.push_back(std::move(cube));
    }
}
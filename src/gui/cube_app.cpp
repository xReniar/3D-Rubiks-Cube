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
    viewerObject.transform.translation.z = -2.5f;
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
        controller.solveCube();

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
    int scaler = 4;
    // defining translation
    /*
    std::vector<glm::vec3> translation{};
    for(int i = -1;i <= 2;i++)
        for(int j = -1;j <= 2;j++)
            for(int k = -1;k <= 2;k++)
                //if(!(i == 0 && j == 0 && k == 0))
                if(!((k == 0 || k == 1) && ((i==0 && j == 0) || (i == 0 && j == 1) || (i==1 && j == 0) || (i == 1) && (j == 1))))
                    translation.push_back(glm::vec3(((float) i)/scaler,((float) j)/scaler,((float) k)/scaler));

    std::vector<std::string> models = {
        "models/blender/corner_yellowOrangeBlue.obj",    // 0
        "models/blender/edge_yellowOrange.obj",          // 1
        "models/blender/edge_yellowOrange.obj",          // 1
        "models/blender/corner_yellowGreenOrange.obj",   // 2
        "models/blender/edge_orangeBlue.obj",            // 3
        "models/blender/center_orange.obj",              // 4
        "models/blender/center_orange.obj",              // 4
        "models/blender/edge_greenOrange.obj",           // 5
        "models/blender/edge_orangeBlue.obj",            // 3
        "models/blender/center_orange.obj",              // 4
        "models/blender/center_orange.obj",              // 4
        "models/blender/edge_greenOrange.obj",           // 5
        "models/blender/corner_whiteOrangeBlue.obj",     // 6
        "models/blender/edge_whiteOrange.obj",           // 7
        "models/blender/edge_whiteOrange.obj",           // 7
        "models/blender/corner_whiteGreenOrange.obj",    // 8
        "models/blender/edge_yellowBlue.obj",            // 9
        "models/blender/center_yellow.obj",              // 10
        "models/blender/center_yellow.obj",              // 10
        "models/blender/edge_yellowGreen.obj",           // 11
        "models/blender/center_blue.obj",                // 12
        "models/blender/center_green.obj",               // 13
        "models/blender/center_blue.obj",                // 12
        "models/blender/center_green.obj",               // 13
        "models/blender/edge_whiteBlue.obj",             // 14
        "models/blender/center_white.obj",               // 15
        "models/blender/center_white.obj",               // 15
        "models/blender/edge_whiteGreen.obj",            // 16
        "models/blender/edge_yellowBlue.obj",            // 9
        "models/blender/center_yellow.obj",              // 10
        "models/blender/center_yellow.obj",              // 10
        "models/blender/edge_yellowGreen.obj",           // 11
        "models/blender/center_blue.obj",                // 12
        "models/blender/center_green.obj",               // 13
        "models/blender/center_blue.obj",                // 12
        "models/blender/center_green.obj",               // 13
        "models/blender/edge_whiteBlue.obj",             // 14
        "models/blender/center_white.obj",               // 15
        "models/blender/center_white.obj",               // 15
        "models/blender/edge_whiteGreen.obj",            // 16 //
        "models/blender/corner_yellowBlueRed.obj",       // 17
        "models/blender/edge_yellowRed.obj",             // 18
        "models/blender/edge_yellowRed.obj",             // 18
        "models/blender/corner_yellowRedGreen.obj",      // 19
        "models/blender/edge_blueRed.obj",               // 20
        "models/blender/center_red.obj",                 // 21
        "models/blender/center_red.obj",                 // 21
        "models/blender/edge_redGreen.obj",              // 22
        "models/blender/edge_blueRed.obj",               // 20
        "models/blender/center_red.obj",                 // 21
        "models/blender/center_red.obj",                 // 21
        "models/blender/edge_redGreen.obj",              // 22
        "models/blender/corner_whiteBlueRed.obj",        // 23
        "models/blender/edge_whiteRed.obj",              // 24
        "models/blender/edge_whiteRed.obj",              // 24
        "models/blender/corner_whiteRedGreen.obj"        // 25
    };
    */
    std::vector<glm::vec3> translation{};
    for(int i = -1;i <= 1;i++)
        for(int j = -1;j <= 1;j++)
            for(int k = -1;k <= 1;k++)
                if(!(i == 0 && j == 0 && k == 0))
                    translation.push_back(glm::vec3(((float) i)/scaler,((float) j)/scaler,((float) k)/scaler));

    std::vector<std::string> models = {
        "models/original/corner_yellowOrangeBlue.obj",    // 0
        "models/original/edge_yellowOrange.obj",          // 1
        "models/original/corner_yellowGreenOrange.obj",   // 2
        "models/original/edge_orangeBlue.obj",            // 3
        "models/original/center_orange.obj",              // 4
        "models/original/edge_greenOrange.obj",           // 5
        "models/original/corner_whiteOrangeBlue.obj",     // 6
        "models/original/edge_whiteOrange.obj",           // 7
        "models/original/corner_whiteGreenOrange.obj",    // 8
        "models/original/edge_yellowBlue.obj",            // 9
        "models/original/center_yellow.obj",              // 10
        "models/original/edge_yellowGreen.obj",           // 11
        "models/original/center_blue.obj",                // 12
        "models/original/center_green.obj",               // 13
        "models/original/edge_whiteBlue.obj",             // 14
        "models/original/center_white.obj",               // 15
        "models/original/edge_whiteGreen.obj",            // 16
        "models/original/corner_yellowBlueRed.obj",       // 17
        "models/original/edge_yellowRed.obj",             // 18
        "models/original/corner_yellowRedGreen.obj",      // 19
        "models/original/edge_blueRed.obj",               // 20
        "models/original/center_red.obj",                 // 21
        "models/original/edge_redGreen.obj",              // 22
        "models/original/corner_whiteBlueRed.obj",        // 23
        "models/original/edge_whiteRed.obj",              // 24
        "models/original/corner_whiteRedGreen.obj"        // 25
    };

    for(int i = 0;i < models.size(); i++){
        std::shared_ptr<Model> model = Model::createModelFromFile(device, models[i]);
        auto cube = CubeObj::createGameObject();
        cube.model = model;
        cube.transform.translation = translation[i];
        cube.transform.scale = { (float) 1/scaler, (float) 1/scaler, (float) 1/scaler };

        gameObjects.push_back(std::move(cube));
    }
}

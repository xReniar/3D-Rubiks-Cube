#ifndef CUBEGUI_H
#define CUBEGUI_H

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>

const uint32_t WIDTH = 800;
const uint32_t HEIGHT = 600;

class CubeGUI {
public:
    void run();
private:
    void initWindow();
    void initVulkan();
    void createInstance();
    void mainLoop();
    void cleanup();
    GLFWwindow* window;
    VkInstance instance;
};

#endif
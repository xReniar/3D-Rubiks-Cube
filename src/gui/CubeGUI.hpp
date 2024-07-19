#ifndef CUBEGUI_H
#define CUBEGUI_H

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/vec4.hpp>
#include<glm/mat4x4.hpp>
#include<vulkan/vulkan.h>

class CubeGUI {
public:
    void run();
    const uint32_t WIDTH = 800;
    const uint32_t HEIGHT = 600;
private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();
    GLFWwindow* window;
};

#endif
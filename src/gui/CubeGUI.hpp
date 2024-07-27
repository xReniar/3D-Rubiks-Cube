#ifndef CUBEGUI_H
#define CUBEGUI_H

#define GLFW_INCLUDE_VULKAN
#include<GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include<glm/mat4x4.hpp>
#include<glm/vec4.hpp>
#include<iostream>
#include<string>
#include<stdexcept>


class CubeGUI {
public:
    CubeGUI(int w, int h, std::string name);
    ~CubeGUI();

    // delete copy constractor and copy operator
    CubeGUI(const CubeGUI &) = delete;
    CubeGUI &operator=(const CubeGUI &) = delete;

    bool shouldClose() { return glfwWindowShouldClose(window); }
private:
    const int width;
    const int height;
    std::string windowName;
    GLFWwindow* window;

    void initWindow();
};

#endif
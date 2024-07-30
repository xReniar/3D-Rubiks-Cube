#include"cube_gui.hpp"

CubeGUI::CubeGUI(int w, int h, std::string name): width{w}, height{h}, windowName{name} {
    this->initWindow();
}

CubeGUI::~CubeGUI(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void CubeGUI::createWindowSurface(VkInstance instance, VkSurfaceKHR *surface){
    if(glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS)
        throw std::runtime_error("failed to create window surface");
}

void CubeGUI::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void CubeGUI::framebufferResizeCallback(GLFWwindow *glfwWindow, int width, int height){
    auto window = reinterpret_cast<CubeGUI *>(glfwGetWindowUserPointer(glfwWindow));
    window->framebufferResized = true;
    window->width = width;
    window->height = height;
}
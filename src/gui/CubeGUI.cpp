#include"CubeGUI.hpp"

CubeGUI::CubeGUI(int w, int h, std::string name): width{w}, height{h}, windowName{name} {
    this->initWindow();
}

CubeGUI::~CubeGUI(){
    glfwDestroyWindow(window);
    glfwTerminate();
}

void CubeGUI::initWindow(){
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
}

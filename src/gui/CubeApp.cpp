#include"CubeApp.hpp"

void CubeApp::run(){
    while(!cubeGUI.shouldClose()){
        glfwPollEvents();
    }
}
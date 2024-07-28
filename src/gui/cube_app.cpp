#include"cube_app.hpp"

void CubeApp::run(){
    while(!cubeGUI.shouldClose()){
        glfwPollEvents();
    }
}
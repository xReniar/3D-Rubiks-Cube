#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"cube_obj.hpp"
#include"cube_gui.hpp"

class Controller {
public:
    struct KeyMappings {
        int moveLeft = GLFW_KEY_A;
        int moveRight = GLFW_KEY_D;
        int moveForward = GLFW_KEY_W;
        int moveBackward = GLFW_KEY_S;
        int moveUp = GLFW_KEY_E;
        int moveDown = GLFW_KEY_Q;
        int lookLeft = GLFW_KEY_LEFT;
        int lookRight = GLFW_KEY_RIGHT;
        int lookUp = GLFW_KEY_UP;
        int lookDown = GLFW_KEY_DOWN;
    };

    KeyMappings keys{};
    float moveSpeed{3.f};
    float lookSpeed{1.5f};

    void moveInPlaneXZ(GLFWwindow* window, float dt, CubeObj& cubeObj);
};

#endif
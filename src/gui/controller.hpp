#ifndef CONTROLLER_H
#define CONTROLLER_H

#include"cube_obj.hpp"
#include"cube_gui.hpp"
#include"../cube/Cube.hpp"
#include"../solver/Solver.hpp"


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

        int inverse = GLFW_KEY_0;
        int double_turn = GLFW_KEY_9;
        int u_turn = GLFW_KEY_1;
        int d_turn = GLFW_KEY_2;
        int f_turn = GLFW_KEY_3;
        int r_turn = GLFW_KEY_4;
        int b_turn = GLFW_KEY_5;
        int l_turn = GLFW_KEY_6;

        int solve = GLFW_KEY_SPACE;
    };
    
    struct Animation {
        bool U_turn = false;
        bool D_turn = false;
        bool F_turn = false;
        bool R_turn = false;
        bool B_turn = false;
        bool L_turn = false;

        bool isRotating(){ return U_turn || D_turn || F_turn || R_turn || B_turn || L_turn; }
    };
    

    KeyMappings keys{};
    float moveSpeed{3.f};
    float lookSpeed{1.5f};

    float rotationSpeed = glm::radians(540.0f);
    int inverse = 1;
    int numOfTurns = 1;

    bool inverseKeyPressed = false;
    bool doubleTurnKeyPressed = false;
    bool solveKeyPressed = false;

    Animation animation{};
    Cube cube{};
    Solver solver{};

    float oldRotationAngle = 0.0f;
    float currentRotationAngle = 0.0f;
    float targetRotationAngle = 0.0f;

    void orbitAroundCube(GLFWwindow* window, float dt, CubeObj& viewerObject);
    void rotateCube(GLFWwindow* window, float dt, std::vector<CubeObj> &gameObjects);
    void solveCube();

    void rotateAroundAxis(char axis, std::string side, int sign, float dt, std::vector<CubeObj> &gameObjects);
};

#endif
#include"controller.hpp"

#include<iostream>

#include<glm/gtc/epsilon.hpp>
#include<limits>

void Controller::orbitAroundCube(GLFWwindow* window, float dt, CubeObj& viewerObject){
    glm::vec3 rotate{0};
    if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS) rotate.y += 1.f;
    if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS) rotate.y -= 1.f;
    if (glfwGetKey(window, keys.lookUp) == GLFW_PRESS) rotate.x += 1.f;
    if (glfwGetKey(window, keys.lookDown) == GLFW_PRESS) rotate.x -= 1.f;

    if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon()) {
        viewerObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate); 
    }

    // limit pitch values between about +/- 85ish degrees
    viewerObject.transform.rotation.x = glm::clamp(viewerObject.transform.rotation.x, -1.5f, 1.5f);
    viewerObject.transform.rotation.y = glm::mod(viewerObject.transform.rotation.y, glm::two_pi<float>());

    float yaw = viewerObject.transform.rotation.y;
    const glm::vec3 forwardDir{sin(yaw), 0.f, cos(yaw)};
    const glm::vec3 rightDir{forwardDir.z, 0.f, -forwardDir.x};
    const glm::vec3 upDir{0.f, -1.f, 0.f};

    glm::vec3 moveDir{0.f};
    if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS) moveDir += forwardDir;
    if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS) moveDir -= forwardDir;
    if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS) moveDir += rightDir;
    if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS) moveDir -= rightDir;
    if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS) moveDir += upDir;
    if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS) moveDir -= upDir;

    if (glm::dot(moveDir, moveDir) > std::numeric_limits<float>::epsilon()) {
        viewerObject.transform.translation += moveSpeed * dt * glm::normalize(moveDir);
    }
}

void Controller::rotateCube(GLFWwindow* window, float dt, std::vector<CubeObj> &gameObjects){
    if(!solveKeyPressed){
        if(!animation.isRotating()){
            // change moves from clockwise to anticlockwise or viceversa
            if(glfwGetKey(window, keys.inverse) == GLFW_PRESS)
                inverseKeyPressed = true;

            if(glfwGetKey(window, keys.inverse) == GLFW_RELEASE && inverseKeyPressed) {
                inverse *= -1;
                inverseKeyPressed = false;
            }

            // enable/disable double turning
            if(glfwGetKey(window, keys.double_turn) == GLFW_PRESS)
                doubleTurnKeyPressed = true;

            if(glfwGetKey(window, keys.double_turn) == GLFW_RELEASE && doubleTurnKeyPressed) {
                if(numOfTurns == 1)
                    numOfTurns = 2;
                else
                    numOfTurns = 1;
                doubleTurnKeyPressed = false;
            }

            // normal rotations
            if(glfwGetKey(window, keys.u_turn) == GLFW_PRESS && !animation.isRotating())
                animation.U_turn = true;

            if(glfwGetKey(window, keys.d_turn) == GLFW_PRESS && !animation.isRotating())
                animation.D_turn = true;

            if(glfwGetKey(window, keys.f_turn) == GLFW_PRESS && !animation.isRotating())
                animation.F_turn = true;

            if(glfwGetKey(window, keys.r_turn) == GLFW_PRESS && !animation.isRotating())
                animation.R_turn = true;

            if(glfwGetKey(window, keys.b_turn) == GLFW_PRESS && !animation.isRotating())
                animation.B_turn = true;

            if(glfwGetKey(window, keys.l_turn) == GLFW_PRESS && !animation.isRotating())
                animation.L_turn = true;

            if(animation.isRotating())
                targetRotationAngle = glm::radians(turnAngle * numOfTurns);
        }

        if(animation.U_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for (int objId : cube.getFaceId("TOP")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('y', (targetRotationAngle - currentRotationAngle) * inverse, true);
                    obj.transform.coordSystem.rotate('y', glm::radians(90.0f * numOfTurns * inverse));
                }

                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("U2");
                else if(inverse == -1) cube.turn("U'");
                else cube.turn("U");

                animation.U_turn = false;
            } else {
                for (int objId : cube.getFaceId("TOP")) {
                    gameObjects[objId].rotate('y', (currentRotationAngle - oldRotationAngle) * inverse, false);
                }
            }
        }

        if(animation.D_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for (int objId : cube.getFaceId("BOTTOM")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('y', (-(targetRotationAngle - currentRotationAngle) * inverse), true);
                    obj.transform.coordSystem.rotate('y', -glm::radians(90.0f * numOfTurns * inverse));
                }

                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("D2");
                else if(inverse == -1) cube.turn("D'");
                else cube.turn("D");

                animation.D_turn = false;
            } else {
                for (int objId : cube.getFaceId("BOTTOM")) {
                    gameObjects[objId].rotate('y', (-(currentRotationAngle - oldRotationAngle) * inverse), false);
                }
            }
        }

        if(animation.F_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for(int objId : cube.getFaceId("FRONT")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('z', ((targetRotationAngle - currentRotationAngle) * inverse), true);
                    obj.transform.coordSystem.rotate('z', glm::radians(90.0f * numOfTurns * inverse));
                }

                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("F2");
                else if(inverse == -1) cube.turn("F'");
                else cube.turn("F");

                animation.F_turn = false;
            } else {
                for (int objId : cube.getFaceId("FRONT")) {
                    gameObjects[objId].rotate('z', ((currentRotationAngle - oldRotationAngle) * inverse), false);
                }
            }
        }

        if(animation.B_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for(int objId : cube.getFaceId("BACK")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('z', (-(targetRotationAngle - currentRotationAngle) * inverse), true);
                    obj.transform.coordSystem.rotate('z', -glm::radians(90.0f * numOfTurns * inverse));
                }

                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("B2");
                else if(inverse == -1) cube.turn("B'");
                else cube.turn("B");

                animation.B_turn = false;
            } else {
                for (int objId : cube.getFaceId("BACK")) {
                    gameObjects[objId].rotate('z', (-(currentRotationAngle - oldRotationAngle) * inverse), false);
                }
            }
        }

        if(animation.R_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for(int objId : cube.getFaceId("RIGHT")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('x', (-(targetRotationAngle - currentRotationAngle) * inverse), true);
                    obj.transform.coordSystem.rotate('x', -glm::radians(90.0f * numOfTurns * inverse));
                }
                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("R2");
                else if(inverse == -1) cube.turn("R'");
                else cube.turn("R");

                animation.R_turn = false;
            } else {
                for (int objId : cube.getFaceId("RIGHT")) {
                    gameObjects[objId].rotate('x', (-(currentRotationAngle - oldRotationAngle) * inverse), false);
                }
            }
        }

        if(animation.L_turn){
            oldRotationAngle = currentRotationAngle;
            currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

            if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
                for(int objId : cube.getFaceId("LEFT")) {
                    auto& obj = gameObjects[objId];
                    obj.rotate('x', ((targetRotationAngle - currentRotationAngle) * inverse), true);
                    obj.transform.coordSystem.rotate('x', glm::radians(90.0f * numOfTurns * inverse));
                }

                currentRotationAngle = 0.0f;
                if(numOfTurns == 2) cube.turn("L2");
                else if(inverse == -1) cube.turn("L'");
                else cube.turn("L");

                animation.L_turn = false;
            } else {
                for (int objId : cube.getFaceId("LEFT")) {
                    gameObjects[objId].rotate('x', ((currentRotationAngle - oldRotationAngle) * inverse), false);
                }
            }
        }
    }
}

void Controller::solveCube(GLFWwindow* window, float dt, std::vector<CubeObj> &gameObjects){
    /*
    volendo tutte le mosse si fanno alla fine e si scive una funzione di controller simile a Cube::turn dove vengono gestite le animazioni
    */
    if(glfwGetKey(window, keys.solve) == GLFW_PRESS && !solveKeyPressed){
        // implement the solve process
        solveKeyPressed = true;
        // block "free movements"
        std::string solution = solver.getSolution(cube.state());
        solveKeyPressed = false;
    }
}
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
        // change moves from clockwise to anticlockwise or viceversa
        if(glfwGetKey(window, keys.inverse) == GLFW_PRESS)
            inverseKeyPressed = true;

        // check if inverse key has been released
        if(glfwGetKey(window, keys.inverse) == GLFW_RELEASE && inverseKeyPressed) {
            inverse *= -1.0f;
            inverseKeyPressed = false;
        }

        if(glfwGetKey(window, keys.double_turn) == GLFW_PRESS)
            doubleTurnKeyPressed = true;

        if(glfwGetKey(window, keys.double_turn) == GLFW_RELEASE && doubleTurnKeyPressed) {
            if(numOfTurns == 1)
                numOfTurns = 2;
            else
                numOfTurns = 1;
            doubleTurnKeyPressed = false;
        }

        if(!animation.isRotating()){
            if(glfwGetKey(window, keys.r_turn) == GLFW_PRESS && !animation.R_turn){
                target.R_turn -= (turnAngle * inverse) * numOfTurns;
                animation.R_turn = true;
            }

            if(glfwGetKey(window, keys.l_turn) == GLFW_PRESS && !animation.L_turn){
                target.L_turn -= (turnAngle * inverse) * numOfTurns;
                animation.L_turn = true;
            }

            if(glfwGetKey(window, keys.u_turn) == GLFW_PRESS && !animation.U_turn){
                target.U_turn += (turnAngle * inverse) * numOfTurns;
                animation.U_turn = true;
            }

            if(glfwGetKey(window, keys.d_turn) == GLFW_PRESS && !animation.D_turn){
                target.D_turn -= (turnAngle * inverse) * numOfTurns;
                animation.D_turn = true;
            }

            if(glfwGetKey(window, keys.f_turn) == GLFW_PRESS && !animation.F_turn){
                target.F_turn += (turnAngle * inverse) * numOfTurns;
                animation.F_turn = true;
            }

            if(glfwGetKey(window, keys.b_turn) == GLFW_PRESS && !animation.B_turn){
                target.B_turn -= (turnAngle * inverse) * numOfTurns;
                animation.B_turn = true;
            }
        }
        

        if (animation.R_turn) {
            current.R_turn = glm::mix(current.R_turn, target.R_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.R_turn, target.R_turn, 0.01f)) {
                current.R_turn = target.R_turn;
                animation.R_turn = false;
                if(numOfTurns == 2)
                    cube.turn("R2");
                else if(inverse <= 0)
                    cube.turn("R'");
                else
                    cube.turn("R");
            }

            for(int objId : cube.getFaceId("RIGHT")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.x = current.R_turn;
            }
        }

        if (animation.L_turn) {
            current.L_turn = glm::mix(current.L_turn, target.L_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.L_turn, target.L_turn, 0.01f)) {
                current.L_turn = target.L_turn;
                animation.L_turn = false;
                if(numOfTurns == 2)
                    cube.turn("L2");
                else if(inverse <= 0)
                    cube.turn("L'");
                else
                    cube.turn("L");
            }

            for(int objId : cube.getFaceId("LEFT")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.x = current.L_turn;
            }
        }

        if (animation.U_turn) {
            current.U_turn = glm::mix(current.U_turn, target.U_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.U_turn, target.U_turn, 0.01f)) {
                current.U_turn = target.U_turn;
                animation.U_turn = false;
                if(numOfTurns == 2)
                    cube.turn("U2");
                else if(inverse <= 0)
                    cube.turn("U'");
                else
                    cube.turn("U");
            }

            for(int objId : cube.getFaceId("TOP")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.y = current.U_turn;
            }
        }

        if (animation.D_turn) {
            current.D_turn = glm::mix(current.D_turn, target.D_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.D_turn, target.D_turn, 0.01f)) {
                current.D_turn = target.D_turn;
                animation.D_turn = false;
                if(numOfTurns == 2)
                    cube.turn("D2");
                else if(inverse <= 0)
                    cube.turn("D'");
                else
                    cube.turn("D");
            }

            for(int objId : cube.getFaceId("BOTTOM")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.y = current.D_turn;
            }
        }

        if (animation.F_turn) {
            current.F_turn = glm::mix(current.F_turn, target.F_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.F_turn, target.F_turn, 0.01f)) {
                current.F_turn = target.F_turn;
                animation.F_turn = false;
                if(numOfTurns == 2)
                    cube.turn("F2");
                else if(inverse <= 0)
                    cube.turn("F'");
                else
                    cube.turn("F");
            }

            for(int objId : cube.getFaceId("FRONT")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.z = current.F_turn;
            }
        }

        if (animation.B_turn) {
            current.B_turn = glm::mix(current.B_turn, target.B_turn, rotationSpeed * dt);

            if (glm::epsilonEqual(current.B_turn, target.B_turn, 0.01f)) {
                current.B_turn = target.B_turn;
                animation.B_turn = false;
                if(numOfTurns == 2)
                    cube.turn("B2");
                else if(inverse <= 0)
                    cube.turn("B'");
                else
                    cube.turn("B");
            }

            for(int objId : cube.getFaceId("BACK")){
                auto& obj = gameObjects[objId];
                obj.transform.rotation.z = current.B_turn;
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
#include"controller.hpp"

#include<iostream>

#include<glm/gtc/epsilon.hpp>
#include<limits>
#include<thread>

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
            if(glfwGetKey(window, keys.solve) == GLFW_PRESS && !solveKeyPressed && !cube.isSolved()){
                // start calculating solution
                std::cout << "[CONTROLLER] - pressed space, cube turns disabled" << std::endl;
                std::thread solveThread([&](){
                    solver.kociemba(cube.state().c_str());
                });
                solveThread.detach();
                solveKeyPressed = true;
            }

            // change moves from clockwise to anticlockwise or viceversa
            if(glfwGetKey(window, keys.inverse) == GLFW_PRESS)
                inverseKeyPressed = true;

            if(glfwGetKey(window, keys.inverse) == GLFW_RELEASE && inverseKeyPressed) {
                inverse *= -1;
                if(inverse > 0) std::cout << "[CHANGE] - inverse turning disabled" << std::endl;
                else std::cout << "[CHANGE] - inverse turning enabled" << std::endl;
                inverseKeyPressed = false;
            }

            // enable/disable double turning
            if(glfwGetKey(window, keys.double_turn) == GLFW_PRESS)
                doubleTurnKeyPressed = true;

            if(glfwGetKey(window, keys.double_turn) == GLFW_RELEASE && doubleTurnKeyPressed) {
                if(numOfTurns == 1){
                    numOfTurns = 2;
                    std::cout << "[CHANGE] - double turning enabled" << std::endl;
                } else {
                    numOfTurns = 1;
                    std::cout << "[CHANGE] - double turning disabled" << std::endl;
                }
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
                targetRotationAngle = glm::radians(90.0f * numOfTurns * inverse);
        }
    }

    if(animation.U_turn){ rotateAroundAxis('y',"U",1,dt,gameObjects); }
    if(animation.D_turn){ rotateAroundAxis('y',"D",-1,dt,gameObjects); }
    if(animation.F_turn){ rotateAroundAxis('z',"F",1,dt,gameObjects); }
    if(animation.B_turn){ rotateAroundAxis('z',"B",-1,dt,gameObjects); }
    if(animation.R_turn){ rotateAroundAxis('x',"R",-1,dt,gameObjects); }
    if(animation.L_turn){ rotateAroundAxis('x',"L",1,dt,gameObjects); }
}

void Controller::rotateAroundAxis(char axis, std::string side, int sign, float dt, std::vector<CubeObj> &gameObjects){
    oldRotationAngle = currentRotationAngle;
    currentRotationAngle = glm::mix(currentRotationAngle, targetRotationAngle, rotationSpeed * dt);

    if (glm::epsilonEqual(currentRotationAngle, targetRotationAngle, 0.01f)) {
        for(int objId : cube.getFaceId(side)) {
            auto& obj = gameObjects[objId];
            obj.rotate(axis, (sign * (targetRotationAngle - currentRotationAngle)), true);
            obj.transform.coordSystem.rotate(axis, sign * targetRotationAngle);
        }

        currentRotationAngle = 0.0f;
        if(numOfTurns == 2) cube.turn(side + "2");
        else if(inverse == -1) cube.turn(side + "'");
        else cube.turn(side);

        if(side == "U") animation.U_turn = false;
        if(side == "D") animation.D_turn = false;
        if(side == "F") animation.F_turn = false;
        if(side == "R") animation.R_turn = false;
        if(side == "B") animation.B_turn = false;
        if(side == "L") animation.L_turn = false;
    } else {
        for (int objId : cube.getFaceId(side)) {
            gameObjects[objId].rotate(axis, (sign * (currentRotationAngle - oldRotationAngle)), false);
        }
    }
}

void Controller::solveCube(){
    if(solver.solutionReady){
        if(!animation.isRotating()){
            if(solver.solution.size() == 0){
                // reset turn variables
                inverse = 1;
                numOfTurns = 1;
                // reset status variables
                solver.solutionReady = false;
                solveKeyPressed = false;
                std::cout << "[CONTROLLER] - cube solved, cube turns enabled" << std::endl;
            } else {
                // getting first move and then removing it from solution list
                std::string turn = solver.solution.front();
                solver.solution.erase(solver.solution.begin());

                inverse = (turn[1] == '\'') ? -1 : 1;
                numOfTurns = (turn[1] == '2') ? 2 : 1;

                char move = turn[0];
                if(move == 'U') animation.U_turn = true;
                if(move == 'D') animation.D_turn = true;
                if(move == 'F') animation.F_turn = true;
                if(move == 'R') animation.R_turn = true;
                if(move == 'B') animation.B_turn = true;
                if(move == 'L') animation.L_turn = true;
                
                targetRotationAngle = glm::radians(90.0f * numOfTurns * inverse);
            }
        }
    }
}
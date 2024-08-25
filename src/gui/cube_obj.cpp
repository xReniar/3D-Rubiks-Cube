#include"cube_obj.hpp"

void CubeObj::rotate(char plane, float angle, bool toRound){
    glm::vec3 axis{};
    if(plane == 'x') axis = glm::vec3(1.0f, 0.0f, 0.0f);
    if(plane == 'y') axis = glm::vec3(0.0f, 1.0f, 0.0f);
    if(plane == 'z') axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);

    // in questa versione si riduce il raggio di rotazione e si ruota intorno al centro del cubo
    glm::vec3 relativePos = (transform.translation) * 1.0f;
    glm::vec4 rotatedPos = rotationMatrix * glm::vec4(relativePos, 1.0f);
    transform.translation = glm::vec3(rotatedPos);

    // Applica la rotazione all'orientamento del pezzo
    char correct_plane;
    int sign;

    std::vector<char> xyz{'x','y','z'};
    for(char _plane_ : xyz){
        char _plane_res_ = std::get<0>(transform.coordSystem.getAxis(_plane_));
        char _sign_res_ = std::get<1>(transform.coordSystem.getAxis(_plane_));
        if(_plane_res_ == plane){
            correct_plane = _plane_;
            sign = _sign_res_;
        }
    }
    glm::quat rotMatrix{};
    if(correct_plane == 'x') rotMatrix = glm::rotate(glm::mat4(1.0f), sign * angle, glm::vec3(1.0f, 0.0f, 0.0f));
    if(correct_plane == 'y') rotMatrix = glm::rotate(glm::mat4(1.0f), sign * angle, glm::vec3(0.0f, 1.0f, 0.0f));
    if(correct_plane == 'z') rotMatrix = glm::rotate(glm::mat4(1.0f), sign * angle, glm::vec3(0.0f, 0.0f, 1.0f));

    transform.quatRotation = transform.quatRotation * rotMatrix;

    if(toRound){

    }
}
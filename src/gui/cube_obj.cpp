#include"cube_obj.hpp"

void CubeObj::rotate(char plane, float angle, bool toRound){
    glm::vec3 axis{};
    if(plane == 'x') axis = glm::vec3(1.0f, 0.0f, 0.0f);
    if(plane == 'y') axis = glm::vec3(0.0f, 1.0f, 0.0f);
    if(plane == 'z') axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);

    // in questa versione si riduce il raggio di rotazione e si ruota intorno al centro del cubo
    glm::vec3 relativePos = (transform.translation - glm::vec3(0.0f, 0.0f, 2.5f)) * 1.0f;
    glm::vec4 rotatedPos = rotationMatrix * glm::vec4(relativePos, 1.0f);
    transform.translation = glm::vec3(rotatedPos) + glm::vec3(0.0f, 0.0f, 2.5f);

    // Applica la rotazione all'orientamento del pezzo
    glm::quat currentRotation = glm::quat(transform.rotation);
    glm::quat rotationQuat = glm::quat(glm::rotate(glm::mat4(1.0f), angle, axis));
    glm::quat newRotation = rotationQuat * currentRotation;
    transform.rotation = glm::eulerAngles(newRotation);

    // rendi positivo lo 0 meno
    if(transform.rotation.x == -0.0f) transform.rotation.x = 0.0f;
    if(transform.rotation.y == -0.0f) transform.rotation.y = 0.0f;
    if(transform.rotation.z == -0.0f) transform.rotation.z = 0.0f;

    if(toRound){
        if(axis.x == 1.0f) transform.rotation.x = glm::radians(round(glm::degrees(transform.rotation.x)));
        if(axis.y == 1.0f) transform.rotation.y = glm::radians(round(glm::degrees(transform.rotation.y)));
        if(axis.z == 1.0f) transform.rotation.z = glm::radians(round(glm::degrees(transform.rotation.z)));

        if(std::fabs(transform.rotation.x) < 1) transform.rotation.x = 0.0f;
        if(std::fabs(transform.rotation.y) < 1) transform.rotation.y = 0.0f;
        if(std::fabs(transform.rotation.z) < 1) transform.rotation.z = 0.0f;
    }

    /*
    std::cout << transform.rotation.x << ", "
              << transform.rotation.y << ", "
              << transform.rotation.z << std::endl;
    std::cout << "---------------------------" << std::endl;
    */
}
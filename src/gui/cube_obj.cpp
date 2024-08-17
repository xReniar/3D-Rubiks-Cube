#include"cube_obj.hpp"

void CubeObj::rotate(const glm::vec3& axis, float angle, bool toRound){
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

    if(toRound){
        if(axis.x == 1.0f) transform.rotation.x = glm::radians(round(glm::degrees(transform.rotation.x)));
        if(axis.y == 1.0f) transform.rotation.y = glm::radians(round(glm::degrees(transform.rotation.y)));
        if(axis.z == 1.0f) transform.rotation.z = glm::radians(round(glm::degrees(transform.rotation.z)));
    }
}

/*
void CubeObj::rotateGlobal(const glm::vec3& axis, float angle) {
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);

    // Calcola la posizione relativa al centro
    glm::vec3 relativePos = transform.translation - glm::vec3(0.0f, 0.0f, 2.5f);
    
    // Scala il raggio di rotazione
    relativePos *= 1.0f;

    // Applica la rotazione
    glm::vec4 rotatedPos = rotationMatrix * glm::vec4(relativePos, 1.0f);

    // Interpola tra la posizione corrente e quella ruotata
    glm::vec3 newPos = glm::mix(transform.translation, glm::vec3(rotatedPos) + glm::vec3(0.0f, 0.0f, 2.5f), angle);
    transform.translation = newPos;

    // Applica la rotazione all'orientamento del pezzo
    glm::quat currentRotation = glm::quat(transform.rotation);
    glm::quat targetRotation = glm::quat(rotationMatrix) * currentRotation;
    glm::quat newRotation = glm::slerp(currentRotation, targetRotation, 1.0f);
    transform.rotation = glm::eulerAngles(newRotation);

    // Aggiorna il sistema di coordinate locale
    glm::mat3 rotMat3 = glm::mat3(glm::mat4_cast(newRotation));
    transform.coordinateSystem.i = rotMat3 * glm::vec3(1.0f, 0.0f, 0.0f);
    transform.coordinateSystem.j = rotMat3 * glm::vec3(0.0f, 1.0f, 0.0f);
    transform.coordinateSystem.k = rotMat3 * glm::vec3(0.0f, 0.0f, 1.0f);
}
*/
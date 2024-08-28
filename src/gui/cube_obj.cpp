#include"cube_obj.hpp"

void CubeObj::rotate(char plane, float angle, bool toRound){
    // rotation step
    glm::vec3 axis{};
    if(plane == 'x') axis = glm::vec3(1.0f, 0.0f, 0.0f);
    if(plane == 'y') axis = glm::vec3(0.0f, 1.0f, 0.0f);
    if(plane == 'z') axis = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, axis);
    transform.translation = glm::vec3(rotationMatrix * glm::vec4(transform.translation, 1.0f));

    // orientation step
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
    float sin = std::sin(sign * angle * 0.5f);
    float cos = std::cos(sign * angle * 0.5f);
    if(correct_plane == 'x') rotMatrix = glm::quat(cos, sin , 0.0f, 0.0f);
    if(correct_plane == 'y') rotMatrix = glm::quat(cos, 0.0f , sin, 0.0f);
    if(correct_plane == 'z') rotMatrix = glm::quat(cos, 0.0f , 0.0f, sin);

    transform.quatRotation = transform.quatRotation * rotMatrix;

    // rounding step
    if(toRound){
        // approximate translation
        transform.translation = glm::round(transform.translation / 0.001f) * 0.001f;

        // approximate orientation
        float components[4] = {transform.quatRotation.w, transform.quatRotation.x, transform.quatRotation.y, transform.quatRotation.z};
        for(int i = 0; i < 4; ++i) {
            // when value is near 0
            components[i] = std::abs(components[i]) < 1e-3f ? 0.0f : components[i];
            // when value is near +1 or -1
            components[i] = std::abs(components[i]) > 0.9f ? std::round(components[i] / 0.001f) * 0.001f : components[i];
            // when value is near 0.5 or -0.5
            components[i] = std::abs(std::abs(components[i]) - 0.5f) < 0.05f ? std::round(components[i] / 0.001f) * 0.001f : components[i];
        }
        transform.quatRotation.w = components[0];
        transform.quatRotation.x = components[1];
        transform.quatRotation.y = components[2];
        transform.quatRotation.z = components[3];
    }
}
#include"cube_obj.hpp"

glm::vec3 CoordSystem::approximate(const glm::vec3& v) {
    const float epsilon = 1e-6f;
    return glm::vec3(
        std::abs(v.x) < epsilon ? 0.0f : v.x,
        std::abs(v.y) < epsilon ? 0.0f : v.y,
        std::abs(v.z) < epsilon ? 0.0f : v.z
    );
}

void CoordSystem::rotate(char plane, float angle){
        glm::mat4 rotationMatrix{1.f};
        if(plane == 'x') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
        if(plane == 'y') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        if(plane == 'z') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

        i = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(i, 0.0f))));
        j = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(j, 0.0f))));
        k = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(k, 0.0f))));
    }

std::tuple<char, int> CoordSystem::getAxis(char axis) {
    glm::vec3 vec;
    std::tuple<char, int> res;
    if (axis == 'x') vec = i;
    if (axis == 'y') vec = j;
    if (axis == 'z') vec = k;

    if (vec.x != 0.0f) { std::get<0>(res) = 'x'; std::get<1>(res) = int(vec.x); }
    if (vec.y != 0.0f) { std::get<0>(res) = 'y'; std::get<1>(res) = int(vec.y); }
    if (vec.z != 0.0f) { std::get<0>(res) = 'z'; std::get<1>(res) = int(vec.z); }

    return res;
}

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
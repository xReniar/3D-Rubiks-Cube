#ifndef CUBE_OBJ_H
#define CUBE_OBJ_H

#include"model.hpp"
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<memory>
#include<map>
#include <tuple>

struct CoordSystem {
    glm::vec3 i{1.0f, 0.0f, 0.0f};
    glm::vec3 j{0.0f, 1.0f, 0.0f};
    glm::vec3 k{0.0f, 0.0f, 1.0f};

    glm::mat4 rotationMatrix{1.f};

    glm::vec3 approximate(const glm::vec3& v) {
        const float epsilon = 1e-6f;
        return glm::vec3(
            std::abs(v.x) < epsilon ? 0.0f : v.x,
            std::abs(v.y) < epsilon ? 0.0f : v.y,
            std::abs(v.z) < epsilon ? 0.0f : v.z
        );
    }

    void rotate(char plane, float angle){
        if(plane == 'x') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(1.0f, 0.0f, 0.0f));
        if(plane == 'y') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 1.0f, 0.0f));
        if(plane == 'z') rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0.0f, 0.0f, 1.0f));

        i = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(i, 0.0f))));
        j = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(j, 0.0f))));
        k = glm::normalize(approximate(glm::vec3(rotationMatrix * glm::vec4(k, 0.0f))));
    }

    std::tuple<char, int> getAxis(char axis) {
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
};

struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{ 1.f, 1.f, 1.f };
    glm::vec3 rotation{}; // for camera
    CoordSystem coordSystem{};
    glm::mat4 mat4_camera(){
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.y);
        const float s2 = glm::sin(rotation.y);
        const float c1 = glm::cos(rotation.x);
        const float s1 = glm::sin(rotation.x);

        return glm::mat4{
            {
                scale.x * (c2 * c3),
                scale.x * (c2 * s3),
                scale.x * (-s2),
                0.0f,
            },
            {
                scale.y * ((s1 * s2 * c3) - (c1 * s3)),
                scale.y * ((s1 * s2 * s3) + (c1 * c3)),
                scale.y * (s1 * c2),
                0.0f,
            },
            {
                scale.z * ((c1 * s2 * c3) + (s1 * s3)),
                scale.z * ((c1 * s2 * s3) - (s1 * c3)),
                scale.z * (c1 * c2),
                0.0f,
            },
            {translation.x, translation.y, translation.z, 1.0f}
        };
    }

    glm::quat quatRotation{1.0f, 0.0f, 0.0f, 0.0f};; // for cube
    glm::mat4 mat4(){
        glm::mat4 transform = glm::mat4(1.0f);

        transform = glm::translate(transform, translation);
        transform = transform * glm::mat4_cast(quatRotation);
        transform = glm::scale(transform, scale);

        return transform;

    }
};

class CubeObj {
public:
    using id_t = unsigned int;

    static CubeObj createGameObject(){
        static id_t currentId = 0;
        return CubeObj { currentId++ };
    }

    CubeObj(const CubeObj &) = delete;
    CubeObj &operator=(const CubeObj &) = delete;
    CubeObj(CubeObj &&) = default;
    CubeObj &operator=(CubeObj &&) = default;

    id_t getId() { return id; }
    
    std::shared_ptr<Model> model{};
    glm::vec3 color{};
    TransformComponent transform{};
    float epsilon = glm::radians(1.0f);

    //const glm::vec3& axis
    void rotate(char plane, float angle, bool toRound);
private:
    id_t id;

    CubeObj(id_t objId): id{objId}{}
};

#endif
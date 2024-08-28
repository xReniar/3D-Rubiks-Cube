#ifndef CUBE_OBJ_H
#define CUBE_OBJ_H

#include"model.hpp"
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<memory>
#include<map>
#include<tuple>

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
    CoordSystem coordSystem{};
    glm::vec3 rotation{}; // for camera
    glm::quat quatRotation{1.0f, 0.0f, 0.0f, 0.0f};; // for cube
    
    glm::mat4 mat4(){
        const float w = quatRotation.w;
        const float x = quatRotation.x;
        const float y = quatRotation.y;
        const float z = quatRotation.z;

        return glm::mat4{
            {
                scale.x * (1 - 2*glm::pow(y,2) - 2*glm::pow(z,2)),
                scale.x * (2*(x * y) + 2*(z * w)),
                scale.x * (2*(x * z) - 2*(y * w)),
                0.0f,
            },
            {
                scale.y * (2*(x * y) - 2*(z * w)),
                scale.y * (1 - 2*glm::pow(x,2) - 2*glm::pow(z,2)),
                scale.y * (2*(y * z) + 2*(x * w)),
                0.0f,
            },
            {
                scale.z * (2*(x * z) + 2*(y * w)),
                scale.z * (2*(y * z) - 2*(x * w)),
                scale.z * (1 - 2*glm::pow(x,2) - 2*glm::pow(y,2)),
                0.0f,
            },
            {translation.x, translation.y, translation.z, 1.0f}
        };

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

    void rotate(char plane, float angle, bool toRound);
private:
    id_t id;

    CubeObj(id_t objId): id{objId}{}
};

#endif
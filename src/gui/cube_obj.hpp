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

    glm::vec3 approximate(const glm::vec3& v);
    void rotate(char plane, float angle);
    std::tuple<char, int> getAxis(char axis);
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
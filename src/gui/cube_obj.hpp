#ifndef CUBE_OBJ_H
#define CUBE_OBJ_H

#include"model.hpp"
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<memory>
#include<map>

struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{ 1.f, 1.f, 1.f };
    glm::vec3 rotation{};

    glm::mat4 mat4(){
        /*
        glm::quat rotationQuat = glm::quat(rotation);
        // Crea la matrice di trasformazione
        glm::mat4 transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, translation);
        transformMatrix = transformMatrix * glm::mat4_cast(rotationQuat);
        transformMatrix = glm::scale(transformMatrix, scale);
        return transformMatrix;
        */
        
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

    void rotate(const glm::vec3& axis, float angle, bool toRound);
private:
    id_t id;

    float rotationSpeed = glm::radians(360.0f);
    CubeObj(id_t objId): id{objId}{}
};

#endif
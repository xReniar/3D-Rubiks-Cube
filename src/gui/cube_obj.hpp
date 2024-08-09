#ifndef CUBE_OBJ_H
#define CUBE_OBJ_H

#include"model.hpp"
#include<glm/gtc/quaternion.hpp>
#include<glm/gtx/quaternion.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<memory>
#include<map>

struct CoordinateSystem {
    glm::vec3 i{1.0f, 0.0f, 0.0f};
    glm::vec3 j{0.0f, 1.0f, 0.0f};
    glm::vec3 k{0.0f, 0.0f, 1.0f};

    glm::vec3 approximate(const glm::vec3& v) {
        const float epsilon = 1e-6f;
        return glm::vec3(
            std::abs(v.x) < epsilon ? 0.0f : v.x,
            std::abs(v.y) < epsilon ? 0.0f : v.y,
            std::abs(v.z) < epsilon ? 0.0f : v.z
        );
    }

    void rotate(char plane, float angle){
        glm::mat3 rotMat{};
        if(plane == 'x'){
            rotMat = {
                {1.0f, 0.0f, 0.0f},
                {0.0f, glm::cos(angle), glm::sin(angle)},
                {0.0f, -glm::sin(angle), glm::cos(angle)}};
        } else if(plane == 'y'){
            rotMat = {
                {glm::cos(angle), 0.0f, -glm::sin(angle)},
                {0.0f, 1, 0.0f},
                {glm::sin(angle), 0, glm::cos(angle)}};
        } else {
            rotMat = {
                {glm::cos(angle), glm::sin(angle), 0.0f},
                {-glm::sin(angle), glm::cos(angle), 0.0f},
                {0.0f, 0.0f, 1.0f}};
        }

        i = glm::normalize(approximate(rotMat * i));
        j = glm::normalize(approximate(rotMat * j));
        k = glm::normalize(approximate(rotMat * k));
    }
};

struct TransformComponent {
    glm::vec3 translation{};
    glm::vec3 scale{ 1.f, 1.f, 1.f};
    glm::vec3 rotation{};

    CoordinateSystem coordinateSystem;

    glm::mat4 mat4(){
        /*
        glm::quat rotationQuat = glm::quat(glm::radians(rotation));

        // Crea la matrice di trasformazione
        glm::mat4 transformMatrix = glm::mat4(1.0f);
        transformMatrix = glm::translate(transformMatrix, translation);
        transformMatrix = transformMatrix * glm::mat4_cast(rotationQuat);
        transformMatrix = glm::scale(transformMatrix, scale);

        return transformMatrix;
        */
        /*
        const float c3 = glm::cos(rotation.z);
        const float s3 = glm::sin(rotation.z);
        const float c2 = glm::cos(rotation.x);
        const float s2 = glm::sin(rotation.x);
        const float c1 = glm::cos(rotation.y);
        const float s1 = glm::sin(rotation.y);

        return glm::mat4{
        {
            scale.x * (c1 * c3 + s1 * s2 * s3),
            scale.x * (c2 * s3),
            scale.x * (c1 * s2 * s3 - c3 * s1),
            0.0f,
        },
        {
            scale.y * (c3 * s1 * s2 - c1 * s3),
            scale.y * (c2 * c3),
            scale.y * (c1 * c3 * s2 + s1 * s3),
            0.0f,
        },
        {
            scale.z * (c2 * s1),
            scale.z * (-s2),
            scale.z * (c1 * c2),
            0.0f,
        },
        {translation.x, translation.y, translation.z, 1.0f}};
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

    void adjustAxis(std::string rotateSide, float angle);
    void rotate(char plane, float value);
    void showCoordinate();
private:
    id_t id;

    CubeObj(id_t objId): id{objId}{}
};

#endif
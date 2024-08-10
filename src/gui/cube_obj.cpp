#include"cube_obj.hpp"

void CubeObj::adjustAxis(std::string rotateSide, float angle) {
    if(rotateSide == "TOP") transform.coordinateSystem.rotate('y', angle);
    if(rotateSide == "BOTTOM") transform.coordinateSystem.rotate('y', -angle);
    if(rotateSide == "FRONT") transform.coordinateSystem.rotate('z', angle);
    if(rotateSide == "BACK") transform.coordinateSystem.rotate('z', -angle);
    if(rotateSide == "RIGHT") transform.coordinateSystem.rotate('x', -angle);
    if(rotateSide == "LEFT") transform.coordinateSystem.rotate('x', angle);
}

void CubeObj::rotate(char plane, float dt){
    char correctPlane = plane;
    //current.R_turn = glm::mix(current.R_turn, target.R_turn, rotationSpeed * dt);
    if(plane == 'x') transform.rotation.x = glm::mix(transform.rotation.x, transform.targetRotation.x, rotationSpeed * dt);
    if(plane == 'y') transform.rotation.y = glm::mix(transform.rotation.y, transform.targetRotation.y, rotationSpeed * dt);
    if(plane == 'z') transform.rotation.z = glm::mix(transform.rotation.z, transform.targetRotation.z, rotationSpeed * dt);
    /*
    for(const auto& pair : transform.axis)
        if(pair.second.value == plane)
            correctPlane = pair.first;
    */
    //std::cout << correctPlane << std::endl;
    
}

void CubeObj::showCoordinate(){
    std::cout << "x: " <<
        transform.coordinateSystem.i.x << ", " <<
        transform.coordinateSystem.i.y << ", " <<
        transform.coordinateSystem.i.z << std::endl;
    std::cout << "y: " <<
        transform.coordinateSystem.j.x << ", " <<
        transform.coordinateSystem.j.y << ", " <<
        transform.coordinateSystem.j.z << std::endl;
    std::cout << "z: " <<
        transform.coordinateSystem.k.x << ", " <<
        transform.coordinateSystem.k.y << ", " <<
        transform.coordinateSystem.k.z << std::endl;
}
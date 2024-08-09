#include"cube_obj.hpp"

void CubeObj::adjustAxis(std::string rotateSide){
    if(rotateSide == "TOP" || rotateSide == "BOTTOM"){
        int copy = transform.axis['x'];
        transform.axis['x'] = transform.axis['z'];
        transform.axis['z'] = copy;
    }

    if(rotateSide == "FRONT" || rotateSide == "BACK"){
        char copy = transform.axis['x'];
        transform.axis['x'] = transform.axis['y'];
        transform.axis['y'] = copy;
    }

    if(rotateSide == "RIGHT" || rotateSide == "LEFT"){
        char copy = transform.axis['y'];
        transform.axis['y'] = transform.axis['z'];
        transform.axis['z'] = copy;
    }
}

void CubeObj::setAngleAxis(char axis, float value){
    if(transform.axis[axis] == 'x'){
        transform.rotation.x = value;
    }
    
    if(transform.axis[axis] == 'y'){
        transform.rotation.y = value;
    }
    
    if(transform.axis[axis] == 'z'){
        transform.rotation.z = value;
    }
}
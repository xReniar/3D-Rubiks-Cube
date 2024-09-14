#include"Cube3.hpp"

Cube::Cube(){
    top_side = new Side(3 ,YELLOW, {2, 11, 19, 1, 10, 18, 0, 9, 17});
    bottom_side = new Side(3, WHITE, {6, 14, 23, 7, 15, 24, 8, 16, 25});
    front_side = new Side(3, BLUE, {0, 9, 17, 3, 12, 20, 6, 14, 23});
    right_side = new Side(3, RED, {17, 18, 19, 20, 21, 22, 23, 24, 25});
    back_side = new Side(3, GREEN, {19, 11, 2, 22, 13, 5, 25, 16, 8});
    left_side = new Side(3, ORANGE, {2, 1, 0, 5, 4, 3, 8, 7, 6});        
}

void Cube::u_turn(Direction direction){
    /* make a copy */
    Cubie front[3],right[3],back[3],left[3];
    for(int i = 0;i < 3;i++){
        front[i] = front_side->cubie[i];
        right[i] = right_side->cubie[i];
        back[i] = back_side->cubie[i];
        left[i] = left_side->cubie[i];
    }
    /* depending of the direction assign the new cubie */
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            front_side->cubie[i] = right[i];
            right_side->cubie[i] = back[i];
            back_side->cubie[i] = left[i];
            left_side->cubie[i] = front[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            front_side->cubie[i] = left[i];
            right_side->cubie[i] = front[i];
            back_side->cubie[i] = right[i];
            left_side->cubie[i] = back[i];
        }
    }
}

void Cube::d_turn(Direction direction){
    /* make a copy */
    Cubie front[3],right[3],back[3],left[3];
    for(int i = 6;i < 9;i++){
        front[i-6] = front_side->cubie[i];
        right[i-6] = right_side->cubie[i];
        back[i-6] = back_side->cubie[i];
        left[i-6] = left_side->cubie[i];
    }
    /* depending of the direction assign the new cubie */
    if(direction == CLOCKWISE){
        for(int i = 6;i < 9;i++){
            front_side->cubie[i] = left[i-6];
            right_side->cubie[i] = front[i-6];
            back_side->cubie[i] = right[i-6];
            left_side->cubie[i] = back[i-6];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 6;i < 9;i++){
            front_side->cubie[i] = right[i-6];
            right_side->cubie[i] = back[i-6];
            back_side->cubie[i] = left[i-6];
            left_side->cubie[i] = front[i-6];
        }
    }
}

void Cube::f_turn(Direction direction){
    /* make a copy */
    Cubie top[3],right[3],bottom[3],left[3];
    for(int i = 0;i < 3;i++){
        top[i] = top_side->cubie[6+i];
        right[i] = right_side->cubie[i*3];
        bottom[i] = bottom_side->cubie[2-i];
        left[i] = left_side->cubie[8-i*3];
    }
    /* depending of the direction assign the new cubie */
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side->cubie[6+i] = left[i];
            right_side->cubie[i*3] = top[i];
            bottom_side->cubie[2-i] = right[i];
            left_side->cubie[8-i*3] = bottom[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side->cubie[6+i] = right[i];
            right_side->cubie[i*3] = bottom[i];
            bottom_side->cubie[2-i] = left[i];
            left_side->cubie[8-i*3] = top[i];
        }
    }
}

void Cube::r_turn(Direction direction){
    Cubie top[3],back[3],bottom[3],front[3];
    for(int i = 2;i < 9;i=i+3){
        int x = (i - 2)/3;
        top[x] = top_side->cubie[i];
        front[x] = front_side->cubie[i];
        bottom[x] = bottom_side->cubie[i];
        back[x] = back_side->cubie[8-i];
    }
    if(direction == CLOCKWISE){
        for(int i = 2;i < 9;i=i+3){
            int x = (i - 2)/3;
            top_side->cubie[i] = front[x];
            front_side->cubie[i] = bottom[x];
            bottom_side->cubie[i] = back[x];
            back_side->cubie[8-i] = top[x];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 2;i < 9;i=i+3){
            int x = (i - 2)/3;
            top_side->cubie[i] = back[x];
            front_side->cubie[i] = top[x];
            bottom_side->cubie[i] = front[x];
            back_side->cubie[8-i] = bottom[x];
        }
    }
}

void Cube::b_turn(Direction direction){
    Cubie top[3],right[3],bottom[3],left[3];
    for(int i = 0;i < 3;i++){
        top[i] = top_side->cubie[i];
        right[i] = right_side->cubie[2+(i*3)];
        bottom[i] = bottom_side->cubie[8-i];
        left[i] = left_side->cubie[6-(i*3)];
    }
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side->cubie[i] = right[i];
            right_side->cubie[2+(i*3)] = bottom[i]; 
            bottom_side->cubie[8-i] = left[i];
            left_side->cubie[6-(i*3)] = top[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side->cubie[i] = left[i];
            right_side->cubie[2+(i*3)] = top[i]; 
            bottom_side->cubie[8-i] = right[i];
            left_side->cubie[6-(i*3)] = bottom[i];
        }
    }
}

void Cube::l_turn(Direction direction){
    Cubie top[3],back[3],bottom[3],front[3];
    for(int i = 0;i < 7;i=i+3){
        int x = i/3;
        top[x] = top_side->cubie[i];
        front[x] = front_side->cubie[i];
        bottom[x] = bottom_side->cubie[i];
        back[x] = back_side->cubie[8-i];
    }
    if(direction == CLOCKWISE){
        for(int i = 0;i < 7;i=i+3){
            int x = i/3;
            top_side->cubie[i] = back[x];
            front_side->cubie[i] = top[x];
            bottom_side->cubie[i] = front[x];
            back_side->cubie[8-i] = bottom[x];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 7;i=i+3){
            int x = i/3;
            top_side->cubie[i] = front[x];
            front_side->cubie[i] = bottom[x];
            bottom_side->cubie[i] = back[x];
            back_side->cubie[8-i] = top[x];
        }
    }
}

void Cube::rotate(_Side_ side,Direction direction){
    if(side == TOP_SIDE){
        top_side->turn(direction);
        u_turn(direction);
    }
    if(side == BOTTOM_SIDE){
        bottom_side->turn(direction);
        d_turn(direction);
    }
    if(side == FRONT_SIDE){
        front_side->turn(direction);
        f_turn(direction);
    }
    if(side == RIGHT_SIDE){
        right_side->turn(direction);
        r_turn(direction);
    }
    if(side == BACK_SIDE){
        back_side->turn(direction);
        b_turn(direction);
    }
    if(side == LEFT_SIDE){
        left_side->turn(direction);
        l_turn(direction);
    }
}

void Cube::turn(const std::string& str){
    Direction direction = CLOCKWISE;
    int turns = 1;
    for(int i = 0;i < str.length();i++){
        // check if there are (') or (2)
        if(i != str.length() && str[i + 1] == '\'') direction = ANTICLOCKWISE;
        if(i != str.length() && (str[i + 1] >= '0' && str[i + 1] <= '9')) turns = (str[i + 1] - '0');

        // execute move
        for(int j = 0;j < turns;j++){
            if(str[i] == 'U')
                rotate(TOP_SIDE,direction);
            if(str[i] == 'D')
                rotate(BOTTOM_SIDE,direction);
            if(str[i] == 'F')
                rotate(FRONT_SIDE,direction);
            if(str[i] == 'R')
                rotate(RIGHT_SIDE,direction);
            if(str[i] == 'B')
                rotate(BACK_SIDE,direction);
            if(str[i] == 'L')
                rotate(LEFT_SIDE,direction);
        }

        // reset direction and turns values
        if(direction == ANTICLOCKWISE || turns > 1){
            direction = CLOCKWISE;
            turns = 1;
            i++;
        }
    }
}

char f(Cubie cubie){
    switch(cubie.color){
        case YELLOW: return 'U';
        case WHITE: return 'D';
        case BLUE: return 'F';
        case RED: return 'R';
        case GREEN: return 'B';
        case ORANGE: return 'L';
    }
    return 'x';
}

std::string Cube::state(){
    std::vector<char> cubeState;
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(top_side->cubie[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(right_side->cubie[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(front_side->cubie[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(bottom_side->cubie[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(left_side->cubie[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(back_side->cubie[i]));

    std::string str(cubeState.begin(), cubeState.end());
    return str;
}

std::vector<int> Cube::getFaceId(std::string side){
    std::vector<int> faceId;
    Side* requestedSide;
    if(side == "U") requestedSide = this->top_side;
    if(side == "D") requestedSide = this->bottom_side;
    if(side == "F") requestedSide = this->front_side;
    if(side == "R") requestedSide = this->right_side;
    if(side == "B") requestedSide = this->back_side;
    if(side == "L") requestedSide = this->left_side;

    for(int i = 0;i < 9;i++)
        faceId.push_back(requestedSide->cubie[i].id);
        
    return faceId;
}

bool Cube::isSolved(){
    return this->state() == "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
}
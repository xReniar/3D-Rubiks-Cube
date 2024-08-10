#include"Cube.hpp"

Cube::Cube():
    top_side(YELLOW, {24, 8, 23, 9, 0, 7, 25, 6, 22}),
    bottom_side(WHITE, {21, 10, 18, 13, 1, 11, 20, 12, 19}),
    front_side(BLUE, {25, 6, 22, 17, 2, 14, 21, 10, 18}),
    right_side(RED, {22, 7, 23, 14, 3, 15, 18, 11, 19}),
    back_side(GREEN, {23, 8, 24, 15, 4, 16, 19, 12, 20}),
    left_side(ORANGE, {24, 9, 25, 16, 5, 17, 20, 13, 21}){
        
    }

void Cube::u_turn(Direction direction){
    /* make a copy */
    Cubie front[3],right[3],back[3],left[3];
    for(int i = 0;i < 3;i++){
        front[i] = front_side.slot[i];
        right[i] = right_side.slot[i];
        back[i] = back_side.slot[i];
        left[i] = left_side.slot[i];
    }
    /* depending of the direction assign the new slot */
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            front_side.slot[i] = right[i];
            right_side.slot[i] = back[i];
            back_side.slot[i] = left[i];
            left_side.slot[i] = front[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            front_side.slot[i] = left[i];
            right_side.slot[i] = front[i];
            back_side.slot[i] = right[i];
            left_side.slot[i] = back[i];
        }
    }
}

void Cube::d_turn(Direction direction){
    /* make a copy */
    Cubie front[3],right[3],back[3],left[3];
    for(int i = 6;i < 9;i++){
        front[i-6] = front_side.slot[i];
        right[i-6] = right_side.slot[i];
        back[i-6] = back_side.slot[i];
        left[i-6] = left_side.slot[i];
    }
    /* depending of the direction assign the new slot */
    if(direction == CLOCKWISE){
        for(int i = 6;i < 9;i++){
            front_side.slot[i] = left[i-6];
            right_side.slot[i] = front[i-6];
            back_side.slot[i] = right[i-6];
            left_side.slot[i] = back[i-6];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 6;i < 9;i++){
            front_side.slot[i] = right[i-6];
            right_side.slot[i] = back[i-6];
            back_side.slot[i] = left[i-6];
            left_side.slot[i] = front[i-6];
        }
    }
}

void Cube::f_turn(Direction direction){
    /* make a copy */
    Cubie top[3],right[3],bottom[3],left[3];
    for(int i = 0;i < 3;i++){
        top[i] = top_side.slot[6+i];
        right[i] = right_side.slot[i*3];
        bottom[i] = bottom_side.slot[2-i];
        left[i] = left_side.slot[8-i*3];
    }
    /* depending of the direction assign the new slot */
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side.slot[6+i] = left[i];
            right_side.slot[i*3] = top[i];
            bottom_side.slot[2-i] = right[i];
            left_side.slot[8-i*3] = bottom[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side.slot[6+i] = right[i];
            right_side.slot[i*3] = bottom[i];
            bottom_side.slot[2-i] = left[i];
            left_side.slot[8-i*3] = top[i];
        }
    }
}

void Cube::r_turn(Direction direction){
    Cubie top[3],back[3],bottom[3],front[3];
    for(int i = 2;i < 9;i=i+3){
        int x = (i - 2)/3;
        top[x] = top_side.slot[i];
        front[x] = front_side.slot[i];
        bottom[x] = bottom_side.slot[i];
        back[x] = back_side.slot[8-i];
    }
    if(direction == CLOCKWISE){
        for(int i = 2;i < 9;i=i+3){
            int x = (i - 2)/3;
            top_side.slot[i] = front[x];
            front_side.slot[i] = bottom[x];
            bottom_side.slot[i] = back[x];
            back_side.slot[8-i] = top[x];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 2;i < 9;i=i+3){
            int x = (i - 2)/3;
            top_side.slot[i] = back[x];
            front_side.slot[i] = top[x];
            bottom_side.slot[i] = front[x];
            back_side.slot[8-i] = bottom[x];
        }
    }
}

void Cube::b_turn(Direction direction){
    Cubie top[3],right[3],bottom[3],left[3];
    for(int i = 0;i < 3;i++){
        top[i] = top_side.slot[i];
        right[i] = right_side.slot[2+(i*3)];
        bottom[i] = bottom_side.slot[8-i];
        left[i] = left_side.slot[6-(i*3)];
    }
    if(direction == CLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side.slot[i] = right[i];
            right_side.slot[2+(i*3)] = bottom[i]; 
            bottom_side.slot[8-i] = left[i];
            left_side.slot[6-(i*3)] = top[i];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 3;i++){
            top_side.slot[i] = left[i];
            right_side.slot[2+(i*3)] = top[i]; 
            bottom_side.slot[8-i] = right[i];
            left_side.slot[6-(i*3)] = bottom[i];
        }
    }
}

void Cube::l_turn(Direction direction){
    Cubie top[3],back[3],bottom[3],front[3];
    for(int i = 0;i < 7;i=i+3){
        int x = i/3;
        top[x] = top_side.slot[i];
        front[x] = front_side.slot[i];
        bottom[x] = bottom_side.slot[i];
        back[x] = back_side.slot[8-i];
    }
    if(direction == CLOCKWISE){
        for(int i = 0;i < 7;i=i+3){
            int x = i/3;
            top_side.slot[i] = back[x];
            front_side.slot[i] = top[x];
            bottom_side.slot[i] = front[x];
            back_side.slot[8-i] = bottom[x];
        }
    }
    if(direction == ANTICLOCKWISE){
        for(int i = 0;i < 7;i=i+3){
            int x = i/3;
            top_side.slot[i] = front[x];
            front_side.slot[i] = bottom[x];
            bottom_side.slot[i] = back[x];
            back_side.slot[8-i] = top[x];
        }
    }
}

void Cube::rotate(_Side_ side,Direction direction){
    if(side == TOP_SIDE){
        top_side.turn(direction);
        u_turn(direction);
    }
    if(side == BOTTOM_SIDE){
        bottom_side.turn(direction);
        d_turn(direction);
    }
    if(side == FRONT_SIDE){
        front_side.turn(direction);
        f_turn(direction);
    }
    if(side == RIGHT_SIDE){
        right_side.turn(direction);
        r_turn(direction);
    }
    if(side == BACK_SIDE){
        back_side.turn(direction);
        b_turn(direction);
    }
    if(side == LEFT_SIDE){
        left_side.turn(direction);
        l_turn(direction);
    }
}

void Cube::turn(const std::string& str){
    Direction direction = CLOCKWISE;
    int turns = 1;
    for(int i = 0;i < str.length();i++){
        /* check if there are (') or (2) */
        if(i != str.length() && str[i + 1] == '\'') direction = ANTICLOCKWISE;
        if(i != str.length() && (str[i + 1] >= '0' && str[i + 1] <= '9')) turns = (str[i + 1] - '0');

        /* execute move */
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

        /* reset direction and turns values */
        if(direction == ANTICLOCKWISE || turns > 1){
            direction = CLOCKWISE;
            turns = 1;
            i++;
        }
    }
    //this->show();
}

char f(Cubie slot){
    switch(slot.color){
        case YELLOW: return 'y';
        case WHITE: return 'w';
        case BLUE: return 'b';
        case RED: return 'r';
        case GREEN: return 'g';
        case ORANGE: return 'o';
    }
    return 'x';
}

std::string Cube::state(){
    std::vector<char> cubeState;
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(top_side.slot[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(right_side.slot[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(front_side.slot[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(bottom_side.slot[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(left_side.slot[i]));
    for(int i = 0;i < 9;i++)
        cubeState.push_back(f(back_side.slot[i]));

    std::string str(cubeState.begin(), cubeState.end());
    return str;
}

std::vector<int> Cube::getFaceId(std::string side){
    std::vector<int> faceId;
    Side* requestedSide;
    if(side == "TOP") requestedSide = &(this->top_side);
    if(side == "BOTTOM") requestedSide = &(this->bottom_side);
    if(side == "FRONT") requestedSide = &(this->front_side);
    if(side == "RIGHT") requestedSide = &(this->right_side);
    if(side == "BACK") requestedSide = &(this->back_side);
    if(side == "LEFT") requestedSide = &(this->left_side);

    for(int i = 0;i < 9;i++)
        faceId.push_back(requestedSide->slot[i].id);

    return faceId;
}

void Cube::show(){
    printf("      %c,%c,%c\n",f(top_side.slot[0]),f(top_side.slot[1]),f(top_side.slot[2]));
    printf("      %c,%c,%c\n",f(top_side.slot[3]),f(top_side.slot[4]),f(top_side.slot[5]));
    printf("      %c,%c,%c\n",f(top_side.slot[6]),f(top_side.slot[7]),f(top_side.slot[8]));
    printf("%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c\n",f(left_side.slot[0]),f(left_side.slot[1]),f(left_side.slot[2]),f(front_side.slot[0]),f(front_side.slot[1]),f(front_side.slot[2]),f(right_side.slot[0]),f(right_side.slot[1]),f(right_side.slot[2]),f(back_side.slot[0]),f(back_side.slot[1]),f(back_side.slot[2]));
    printf("%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c\n",f(left_side.slot[3]),f(left_side.slot[4]),f(left_side.slot[5]),f(front_side.slot[3]),f(front_side.slot[4]),f(front_side.slot[5]),f(right_side.slot[3]),f(right_side.slot[4]),f(right_side.slot[5]),f(back_side.slot[3]),f(back_side.slot[4]),f(back_side.slot[5]));
    printf("%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c,%c\n",f(left_side.slot[6]),f(left_side.slot[7]),f(left_side.slot[8]),f(front_side.slot[6]),f(front_side.slot[7]),f(front_side.slot[8]),f(right_side.slot[6]),f(right_side.slot[7]),f(right_side.slot[8]),f(back_side.slot[6]),f(back_side.slot[7]),f(back_side.slot[8]));
    printf("      %c,%c,%c\n",f(bottom_side.slot[0]),f(bottom_side.slot[1]),f(bottom_side.slot[2]));
    printf("      %c,%c,%c\n",f(bottom_side.slot[3]),f(bottom_side.slot[4]),f(bottom_side.slot[5]));
    printf("      %c,%c,%c\n",f(bottom_side.slot[6]),f(bottom_side.slot[7]),f(bottom_side.slot[8]));
    printf("\n");

    /*
    printf("         %2d|%2d|%2d\n", top_side.slot[0].id, top_side.slot[1].id, top_side.slot[2].id);
    printf("         %2d|%2d|%2d\n", top_side.slot[3].id, top_side.slot[4].id, top_side.slot[5].id);
    printf("         %2d|%2d|%2d\n", top_side.slot[6].id, top_side.slot[7].id, top_side.slot[8].id);
    printf("%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d\n", left_side.slot[0].id, left_side.slot[1].id, left_side.slot[2].id, front_side.slot[0].id, front_side.slot[1].id, front_side.slot[2].id, right_side.slot[0].id, right_side.slot[1].id, right_side.slot[2].id, back_side.slot[0].id, back_side.slot[1].id, back_side.slot[2].id);
    printf("%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d\n", left_side.slot[3].id, left_side.slot[4].id, left_side.slot[5].id, front_side.slot[3].id, front_side.slot[4].id, front_side.slot[5].id, right_side.slot[3].id, right_side.slot[4].id, right_side.slot[5].id, back_side.slot[3].id, back_side.slot[4].id, back_side.slot[5].id);
    printf("%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d|%2d\n", left_side.slot[6].id, left_side.slot[7].id, left_side.slot[8].id, front_side.slot[6].id, front_side.slot[7].id, front_side.slot[8].id, right_side.slot[6].id, right_side.slot[7].id, right_side.slot[8].id, back_side.slot[6].id, back_side.slot[7].id, back_side.slot[8].id);
    printf("         %2d|%2d|%2d\n", bottom_side.slot[0].id, bottom_side.slot[1].id, bottom_side.slot[2].id);
    printf("         %2d|%2d|%2d\n", bottom_side.slot[3].id, bottom_side.slot[4].id, bottom_side.slot[5].id);
    printf("         %2d|%2d|%2d\n", bottom_side.slot[6].id, bottom_side.slot[7].id, bottom_side.slot[8].id);
    printf("\n");
    */


    /*
    for(int i = 0;i < 9;i++)
        std::cout << top_side.slot[i].id << "," << std::flush;
    std::cout << "" << std::endl;
    for(int i = 0;i < 9;i++)
        std::cout << bottom_side.slot[i].id << "," << std::flush;
    std::cout << "" << std::endl;
    for(int i = 0;i < 9;i++)
        std::cout << front_side.slot[i].id << "," << std::flush;
    std::cout << "" << std::endl;
    for(int i = 0;i < 9;i++)
        std::cout << right_side.slot[i].id << "," << std::flush;
    std::cout << "" << std::endl;
    for(int i = 0;i < 9;i++)
        std::cout << back_side.slot[i].id << "," << std::flush;
    std::cout << "" << std::endl;
    for(int i = 0;i < 9;i++)
        std::cout << left_side.slot[i].id << "," << std::flush;
    std::cout << "\n--------------------------" << std::endl;
    */
}
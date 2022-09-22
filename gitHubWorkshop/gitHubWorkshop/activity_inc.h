//
// Created by Sabrina on 9/22/2022.
//

#ifndef TEAMTECH22_23_ACTIVITY_INC_H
#define TEAMTECH22_23_ACTIVITY_INC_H
#includ string

unsigned int rand_ele_dis(){
    return rand(200) % -100;
}
double randTime(){
    return rand(200) % -100;
}

char randDir(){
    char direction[4] = {"N", "S", "E", "W"};
    
    return direction[rand() % 5];

}

#endif //TEAMTECH22_23_ACTIVITY_INC_H

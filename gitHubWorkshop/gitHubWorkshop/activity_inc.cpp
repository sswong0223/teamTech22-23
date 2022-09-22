//
// Created by Sabrina on 9/22/2022.
//

#include "activity_inc.h"

#include <iostream>
#include string

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


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
    const char* direction[4] = {"North", "South", "East", "West"};

    return direction[rand() % 5];

}


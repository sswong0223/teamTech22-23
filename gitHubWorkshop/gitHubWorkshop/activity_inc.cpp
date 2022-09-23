//
// Created by Sabrina on 9/22/2022.
//

#include "activity_inc.h"

#include <iostream>
#include string
using namespace std;
class satellite{
    //input attributes: elevation, distance traveled from ground station
    //                  time since access, and travel direction
    unsigned int elevation;
    unsigned int distanceFromGroundStation;
    double timeSinceAccess;
    string travelDirection

public:
    Satellite(){
        elevation = 0;
        distanceFromGroundStation = 0;
        timeSinceAccess = 0.00;
        travelDirection = "North";
    }
    Satellite(unsigned int ele, unsigned int dist, double time, string dir){
        this.elevation = ele;
        this.distanceFromGroundStation = dist;
        this.timeSinceAccess = time;
        this.travelDirection = dir;
    }
    void print(){
        cout<< elevation
    }

};

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


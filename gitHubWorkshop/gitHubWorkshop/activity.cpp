//
// Created by Sabrina on 9/22/2022.
//
#include <iostream>
#include <string>
#include <vector>
#include <random>
using namespace std;
static const char direction[] = "NESW";
unsigned int randEle();
unsigned int randDis();
double doubleRand();
char randDir();
void getRandom(unsigned int &e, unsigned int &dis, double &time, string &dir);

class Satellite{
    //input attributes: elevation, distance traveled from ground station
    //                  time since access, and travel direction
    unsigned int elevation;
    unsigned int distanceFromGroundStation;
    double timeSinceAccess;
    string travelDirection;

public:
    Satellite(){
        elevation = 0;
        distanceFromGroundStation = 0;
        timeSinceAccess = 0.00;
        travelDirection = "North";
    }
    Satellite(unsigned int ele, int dist, double time, string dir){
        elevation = ele;
        distanceFromGroundStation = dist;
        timeSinceAccess = time;
        travelDirection = dir;
    }

    void print(){
        cout<< elevation << " " << distanceFromGroundStation << " " << timeSinceAccess << " " << travelDirection << endl;
    }
    
    unsigned int getDistance(){
        return distanceFromGroundStation;
    }

};



int main(){

    Satellite satellite;
    
    // assign variables for each satellite attribute:
    unsigned int elevation;
    unsigned int distanceFromGroundStation;
    double timeSinceAccess;
    string travelDirection;

    // schedule vector to store 10 satellites
    vector<Satellite> schedule;

    for (int i = 0; i<10; i++){
        //use getRandom() function to get random attribute vaules
        getRandom(elevation, distanceFromGroundStation, timeSinceAccess, travelDirection);
        
        schedule.push_back(Satellite(elevation,distanceFromGroundStation,timeSinceAccess,travelDirection));
    }

    // call the print() function in the Satellite class to display the attributes of each satellite
    for(int i = 0; i<10; i++){
        schedule[i].print();
    }

    // Find the distance 
    int leastDis = schedule[0].getDistance();
    for(int i = 1; i<schedule.size(); i++){
        if(schedule[i].getDistance() < leastDis){
            leastDis = schedule[i].getDistance();
        }
    }
    cout<< "Satellite of the least distance is: "<< endl;
    cout<< leastDis<<endl;

}

unsigned int randEle(){
    return rand() % 100;
}

unsigned int randDis(){
    return rand() % 100;
};

double doubleRand(){
    return double(rand()) / (double(RAND_MAX/100));
}

char randDir(){
    return direction[rand() % (sizeof(direction)-1)];
}

void getRandom(unsigned int &e, unsigned int &dis, double &time, string &dir){
    e = randEle();
    dis = randDis();
    time = doubleRand();
    dir = randDir();
}
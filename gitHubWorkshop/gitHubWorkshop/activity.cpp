//
// NAME: Gabrielle Richards
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
    //inital values of Satellites, don't need to change
    Satellite(){
        elevation = 0;
        distanceFromGroundStation = 0;
        timeSinceAccess = 0.00;
        travelDirection = "North";
    }
    //Contructor with Parameters
    Satellite(unsigned int ele, int dist, double time, string dir){
        //assign each attribute in private to the variable in in the parameters
        elevation = ele;
        distanceFromGroundStation = dist;
        timeSinceAccess = time;
        travelDirection = dir;
    }

    //function to display satellite attributes
    void print(){
        cout<< elevation << " " << distanceFromGroundStation << " " << timeSinceAccess << " " << travelDirection << endl;
    }
    
    //returns the distance from ground station of a satellite
    unsigned int getDistance(){
        return distanceFromGroundStation;
    }

};



int main(){

    Satellite satellite;
    
    // assign variables for each satellite attribute: 
    //Elevation, Distance From Ground Station, Time since Access, travel Direction  
    unsigned int e;
    unsigned int dis;
    double time;
    string dir;
    
    // schedule vector to store 10 satellites
    vector<Satellite> schedule;

    // insert 10 satellites into Schedule vector
    // Hint:-use for loop to iterate through 10 satellite objects
    //      -use getRandom() function to get random attribute vaules
    //      -use .push_back() to input each satellite into the schedule vector
    //          use Satellite class constructor to set satellite attributes
    for (int i = 0; i < 10; ++i)
    {
        getRandom(e, dis, time, dir);
        Satellite obj = Satellite(e, dis, time, dir);
        schedule.push_back(obj);
    }
    
    

    // call the print() function in the Satellite class to display the attributes of each satellite
    // Hint: use for loop to iterate through all index of schedule vector
    for (int i = 0; i < schedule.size(); ++i)
    {
        schedule[i].print();
    }

    

    int leastDistance = schedule[0].getDistance();

    // Find the distance of the satellite closest to the ground station
    // Hint: use a for loop to iterate through the vector 
    //      and an if statement to compare the distance from ground station of each satellite
    for (int i = 1; i < schedule.size(); ++i)
    {
        if (schedule[i].getDistance() < leastDistance)
            leastDistance = schedule[i].getDistance();
    }    
    
    

    cout<< "Satellite of the least distance is: "<< leastDistance << endl;
    // print out found least distance here

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
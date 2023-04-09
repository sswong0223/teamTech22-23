#include <iostream>
#include <vector>
#include <fstream>
#include "libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include "libsgp4/DateTime.h"
#include <vector>
#include <string>
#include <queue>
#include <functional>

using namespace std;
// returns vector of min heap priority queues and takes in 1 satellite object,
// & vector of priority_queue that it needs to be added into
void addSatelliteToHeaps(vector<priority_queue<Satellite, vector<int>, satComparator>>& heap, Satellite& sat); //might change to string if time is in string
//operator overload to be able to compare times in satellite class, change data type of the things in priority_queue later
int main() {

    /*
    // Hard code test:
    // Name: Starlink SSC: 47862  test starlink from Andrew
    libsgp4::DateTime time = libsgp4::DateTime(2022, 10, 19, 13, 50, 45);
    std::string line1 = "1 47862U 21021U   22292.11715278 -.00011170  00000-0 -74838-3 0  2923";
    std::string line2 = "2 47862  53.0547  57.3135 0001386  72.2469 132.6029 15.06412172    18";
    libsgp4::Tle obj1(line1, line2);
    Satellite satellite(obj1, time);
    satellite.generatePasses();
    */

    // DEFAULT DATE TIME
    //needs to be military udt time
    libsgp4::DateTime currentTime(libsgp4::DateTime::Now());

    // Initialize variables for reading input file
    int numRanks = 3; //!!!change later!!!
    std::string buffer;
    //updated March 31,2022 1:48 pm est
    std::fstream input("celestrakList.txt"); // The file of satellites is found in the debug folder
    string line1, line2;

    //Initialize variables for scheduler
    //vector will be a temporary data type to hold satellites, need to decide on a better container to store data
    //(maybe a priority queue/heap)
    vector<Satellite> satellites;
    vector<Satellite> schedule;


    // Read in data from active.txt file until you reach the end of the file
    while(getline(input, buffer)){

        //read TLE lines
        getline(input, line1);
        getline(input, line2);

        //line1.pop_back(); // Gets rid of carriage return character
        //line2.pop_back(); // Gets rid of carriage return character
        //create a TLE object with line 1 and line 2 as arguments
        libsgp4::Tle tle(line1, line2);
        //create a satellite object with the tle as an argument
        Satellite satellite(tle, currentTime);
        vector<priority_queue<Satellite, vector<Satellite>, satComparator>> heaps;
        if(satellite.isLEO()){
            //satellite.generatePasses();
            satellites.push_back(satellite);
            //add satellite object to a max heap prioritized by ranking
            //addSatelliteToHeaps(heaps, satellite);
        }
        

    }

    return 0;
}

void createSchedule(vector<Satellite> schedule, vector<Satellite> satellites) {
    //use greedy algorithm and consider ranks of all satellites to schedule satellites
    //take satellite with the largest ranking from the max heap
    //consider all acceptable access periods of the satellite, find the one with the earliest end time, place it on the schedule
    //Possible changes: have ranking “tiers” and find the satellite with the earliest end time in the highest tier, then add it to the schedule
    for (int i = 0; i < satellites.size(); i++) {
        schedule.push_back(satellites[i]);
    }
}

//to create a metric of the schedule’s effectiveness, would be useful to have count of number of satellites in the schedule
int numSatellites(vector<Satellite> satellites){
    return satellites.size();
}

string printSchedule(vector<Satellite> schedule){
    for (int i = 0; i < schedule.size(); i++) {
        //the satellites toString() will print the specifics for each satellite
        schedule[i].toString();
    }

    /*
     * Output:
     * - How are we planning on storing the output of our algorithm?
     * - Needs to be in a format that the front-end team can easily work with
     */
}

void addSatelliteToHeaps(vector<priority_queue<Satellite, vector<Satellite>, satComparator>>& heap, Satellite& sat){
    //add more if statements if more ranks
    if(sat.getRank() == 1){
        heap[0].push(sat); //push error here because greater::operator won't work correctly?
    }
    else if(sat.getRank() == 2){
        heap[1].push(sat);
    }
    else if(sat.getRank() == 3){
        heap[2].push(sat);
    }
}

float radiansToDegrees(float radians){
    float degrees ;

    degrees = radians * 180 / M_PI ;

    return degrees;

}

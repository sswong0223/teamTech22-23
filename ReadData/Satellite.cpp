#include <iostream>
#include <vector>
#include <fstream>
#include "sgp4-master/libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include <vector>
#include <string>

using namespace std;

int main() {

    /*
    // Hard code test: delete later
    std::string line1 = "1 00900U 64063C   23046.50614910  .00001371  00000+0  14455-2 0  9991";
    std::string line2 = "2 00900  90.1810  45.4651 0027461  15.1398 149.1107 13.74104475904037";
    libsgp4::Tle obj1(line1, line2);
    std::cout << obj1.Name() << std::endl;
*/
    // Initialize variables for reading input file
    std::string buffer;
    std::fstream input("active.txt"); // The file of satellites is found in the debug folder
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

        line1.pop_back(); // Gets rid of carriage return character
        line2.pop_back(); // Gets rid of carriage return character
        //create a TLE object with line 1 and line 2 as arguments
        libsgp4::Tle tle(line1, line2);
        //create a satellite object with the tle as an argument
        Satellite satellite(tle);
        //add satellite object to a max heap prioritized by ranking
        satellites.push_back(satellite);
    }
    //satellites.at(0).printName();

    return 0;
}

void createSchedule() {
    //use greedy algorithm and consider ranks of all satellites to schedule satellites
    //take satellite with the largest ranking from the max heap
    //consider all acceptable access periods of the satellite, find the one with the earliest end time, place it on the schedule
    //Possible changes: have ranking “tiers” and find the satellite with the earliest end time in the highest tier, then add it to the schedule
    for (int i = 0; i < satellites.size(); i++) {
        scheduler.push_back(satellites(i));
    }
}

string printSchedule(){
    for (int i = 0; i < scheduler.size(); i++) {
        //the satellites toString() will print the specifics for each satellite
        cout << scheduler[i] << endl;
    }

    /*
     * Output:
     * - How are we planning on storing the output of our algorithm?
     * - Needs to be in a format that the front-end team can easily work with
     */
}

//to create a metric of the schedule’s effectiveness, would be useful to have count of number of satellites in the schedule
int numSatellites(){
    return satellites.size();
}

//when we want to print out the entire schedule
void ToString(){
    for(string s: schedule){
        //if we change the data type to a class instead of a string, we don't need to extract the substrings
        //to make the output all pretty, so wait to end to finish this function
        cout << s << endl;
    }
}

#include <iostream>
#include <vector>
#include <fstream>
#include "sgp4-master/libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include <vector>
#include <string>

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

    //Initialize variables for scheduler
    //vector will be a temporary data type to hold satellites, need to decide on a better container to store data
    //(maybe a priority queue/heap)
    vector<Satellite> satellites;
    vector<Satellite> schedule;

    // Read in data from active.txt file until you reach the end of the file
    while(std::getline(input, buffer)){
        getline(input, line1);
        getline(input, line2);
        line1.pop_back(); // Gets rid of carriage return character
        line2.pop_back(); // Gets rid of carriage return character
        libsgp4::Tle tle1(line1, line2);
        Satellite satellite(tle1);
        satellites.push_back(satellite);
    }

    satellites.at(0).printName();

    return 0;
}

void createSchedule(){
    /* Make a flowchart of ideas for the scheduling algorithm
     *
     * use greedy algorithm to determine order of satellites, also need to consider:
     * - Which satellite is more "rare" on the schedule ( available to connect to the least)
     * - What is the distance to ground station (aka what orbit is )- more distance = less stable
     * - Angle of elevation
     * - What information is being transmitted
     * - What is the satellite's "job"
     *
     * You won't have all the questions to the questions above at this point in time, so just focus on
     * planning out how you will implement the greedy algorithm in code and the logistics of how the schedule
     * will work.
     *
    */

    //once we determine order of satellites, for every satellite need to call calculateSat()
    for(int i = 0; i < satellites.size(); i++){
        //adding to scheduler when and were the antenna should point
        scheduler.push_back(sat.calculateSat());
        sat.addRanking(i);
    }

    /*
     * Ouput:
     * - How are we planning on storing the output of our algorithm?
     * - Needs to be in a format that the front-end team can easily work with
     */
}

//add satellites to satellites list, not yet to the scheduler
void addSatellite(Satellite sat){
    satellites.push_back(sat);
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

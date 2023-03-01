//
// Created by Clarissa Mac on 3/1/23.
//

#ifndef TESTSGP4_SCHEDULER_H
#define TESTSGP4_SCHEDULER_H

#include "Satellite.h"
#include "libsgp4/Tle.h"
#include <vector>
#include <string>
using namespace std;

class Scheduler {

    private:
        //vector will be a temporary data type to hold satellites, need to decide on container to store data
        //(maybe a priority queue/heap)
        vector<Satellite> satellites;
        //use string as data type for scheduler right now, might make a new class just for where and when antenna
        //should point especially because this is over a 7-day period
        vector<string> schedule;

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



    public:
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
};


#endif //TESTSGP4_SCHEDULER_H

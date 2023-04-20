#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>

#include "libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include "libsgp4/DateTime.h"

#include <vector>
#include <string>
#include <queue>
#include <functional>
#include <iterator>

#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/bsoncxx/builder/basic/document.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/bsoncxx/json.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/bsoncxx/builder/basic/kvp.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/build/src/mongocxx/config/config.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/client.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/instance.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/stdx.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/uri.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/options/client.hpp>
#include </Users/cc/Downloads/TeamTech2022-2023/TestSGP4/mongo-c-driver-1.4.2/mongo-cxx-driver-r3.0.2/src/mongocxx/instance.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::make_document;

using namespace std;
void createSchedule(vector<Satellite>& schedule, vector<priority_queue<Satellite>>& heaps);

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
    vector<Satellite> schedule;

    vector<priority_queue<Satellite>> heaps;
    priority_queue<Satellite> queue1;
    priority_queue<Satellite> queue2;
    priority_queue<Satellite> queue3;
    heaps.push_back(queue1);
    heaps.push_back(queue2);
    heaps.push_back(queue3);

    // Read in data from active.txt file until you reach the end of the file
    while(getline(input, buffer)){
        if(heaps[0].size() > 50){
            break;
        }
        //read TLE lines
        getline(input, line1);
        getline(input, line2);

        //line1.pop_back(); // Gets rid of carriage return character
        //line2.pop_back(); // Gets rid of carriage return character
        //create a TLE object with line 1 and line 2 as arguments
        libsgp4::Tle tle(line1, line2);
        //create a satellite object with the tle as an argument
        Satellite satellite(tle, currentTime);

        if(!satellite.getConstrSuccess()){
            continue;
        }

        if(satellite.isLEO()){
            satellite.generatePasses();
            // Satellite does not pass over
            if(satellite.getNumPasses() == 0){
                continue;
            }
            satellite.toString();
            satellite.assignRank();

            //satellites.push_back(satellite);
            //add satellite object to a max heap prioritized by ranking
            if(satellite.getRank() == 1)
                heaps[0].push(satellite);
            else if(satellite.getRank() == 2)
                heaps[1].push(satellite);
            else if(satellite.getRank() == 3)
                heaps[2].push(satellite);

        }

    }

    createSchedule(schedule, heaps);



    try{
        // Create an instance.
        mongocxx::instance inst{};

        // Replace the connection string with your MongoDB deployment's connection string.
        const auto uri = mongocxx::uri{"mongodb+srv://TeamTech22-23:\"TeamTech22-23\"@satellitecluster.uajispm.mongodb.net/?retryWrites=true&w=majority"};

        // Set the version of the Stable API on the client.
        mongocxx::options::client client_options;
        const auto api = mongocxx::options::server_api{ mongocxx::options::server_api::version::k_version_1 };
        client_options.server_api_opts(api);

        // Setup the connection and get a handle on the "TeamTech" database.
        mongocxx::client conn{ uri, client_options };
        mongocxx::database db = conn["TeamTech"];

        // Ping the database.
        const auto ping_cmd = bsoncxx::builder::basic::make_document(bsoncxx::builder::basic::kvp("ping", 1));
        db.run_command(ping_cmd.view());
        cout << "Pinged your deployment. You successfully connected to MongoDB!" << endl;
    } catch (const std::exception& e){
        // Handle errors.
        cout<< "Exception: " << e.what() << endl;
    }

    //once connected to MongoDB, send the output for all satellites in the schedule to the database
    for(int i = 0; i < schedule.size(); i++){
        auto sat_doc = make_document(
                kvp("name", schedule[i].getName()),
                kvp("startTime", schedule[i].getStartString()),
                kvp("endTime", schedule[i].getEndString()));
        auto insert_one_result = db.insert_one(sat_doc);
    }

    return 0;
}

void createSchedule(vector<Satellite>& schedule, vector<priority_queue<Satellite>>& heaps){

    schedule.push_back(heaps[0].top());
    heaps[0].pop();

    for(int heap_num = 0; heap_num < 3; heap_num++) {
        while (heaps[heap_num].size() > 0) {
            int index = 0;
            Satellite sat = heaps[heap_num].top();
            heaps[heap_num].pop();
            while (index < schedule.size()) {
                if (sat.getStartTime().Compare(schedule[index].getStartTime()) == -1) {
                    break;
                } else {
                    index++;
                }
            }
            auto it = schedule.begin() + index;
            if (index == 0) {
                if (sat.getEndTime().Compare(schedule[index].getStartTime()) == -1) {
                    schedule.insert(it, sat);
                }
            } else if (index == schedule.size()) {
                if(sat.getStartTime().Compare(schedule[index-1].getEndTime()) == 1){
                    schedule.push_back(sat);
                }

            } else {
                if(sat.getStartTime().Compare(schedule[index-1].getEndTime()) == 1 &&
                    sat.getEndTime().Compare(schedule[index].getStartTime()) == -1){
                      schedule.insert(it, sat);
                }
            }
        }
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
}

//
// Created by Clarissa Mac on 3/13/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include <vector>
#include <string>

using namespace std;

//function to calculate - Where and when the antenna should point over a 7-day period (coordinates,
// angles as it changes over a 7-day period, take into account velocity of satellite moving)
void Satellite::calculatePos(float timePassed){
    dt = tle.Epoch().AddMinutes(timePassed);
    //calculate satellite position
    eci = sgp4.FindPosition(dt);
    //get look angle for observer to satellite
    topo = obs.GetLookAngle(eci);
    //convert satellite position to geodetic coordinates
    geo = eci.ToGeodetic();
}

bool Satellite::isLEO(){
    /*
     * * We don't need to even consider the satellites that aren't LEO for the scheduler
        Main Requirements for LEO:
        Inclination: 0-90
        Mean motion: 14-17

        Specifications that also need to be considered are:
        - A minimum elevation above the local horizon and obstructions
        - A minimum duration of 1 minute for an acceptable access
        - A minimum range during the access
        - A preferred direction of travel (ascending pass or descending pass)
        - Access only during “mutual view” where the satellite is in simultaneous view of both the ground control and second designated location
        - A maximum interval between accesses
     */
}

float Satellite::calculateDistance() {
    //need to code calculation for distance between ground station and satellite
    //ground station is 29°38'53.1"N 82°20'51.1"W on top of Weimer Hall
    //angle = arccos(point1 * point2)
    //distance = angle * pi * radius
}

void Satellite::assignRank(){
    //need to code ranking system here (Aerospace team will hopefully provide this)
    //assign variable rank with ranking

}

void Satellite::toString(){
    //need to figure out what output needs to be outputted for each satellite in the 7-day schedule
    //eci can't be outputted as it is, so need to figure out what attributes of eci we need

    //cout << eci << endl;
    cout << topo << endl;
    cout << geo << endl;
}

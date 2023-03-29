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
#include <math.h>

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
    if((tle.Inclination(true) < 0 && tle.Inclination(true) > 90) || (tle.MeanMotion() < 14 && tle.MeanMotion() > 17)) {
        rank = 0;
    }
}

float Satellite::calculateDistance() {
    //need to code calculation for distance between ground station and satellite
    //ground station is 29°38'53.1"N 82°20'51.1"W on top of Weimer Hall
    //angle = arccos(point1 * point2)
    //distance = angle * pi * radius
    double baseLat = 0.834765;
    double baseLon = -1.441374;
    double baseAlt = .009;

    double earthRadius = 6371.0; // Earth's radius in kilometers
    double dLat = this->geo.latitude - baseLat;
    double dLon = this->geo.longitude - baseLon;
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(baseLat) * cos(this->geo.latitude) *
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    double d = earthRadius * c;
    double dh = this->geo.altitude - baseAlt;
    return sqrt(d * d + dh * dh);
}

void Satellite::assignRank(){
    //need to code ranking system here (

    //assign variable rank with ranking

}

void Satellite::toString(){
    //need to figure out what output needs to be outputted for each satellite in the 7-day schedule
    //eci can't be outputted as it is, so need to figure out what attributes of eci we need

    //cout << eci << endl;
    cout << topo << endl;
    cout << geo << endl;
}

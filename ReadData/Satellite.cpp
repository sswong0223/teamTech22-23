//
// Created by Clarissa Mac on 3/13/23.
//

#include <iostream>
#include <vector>
#include <fstream>
#include "libsgp4/SGP4.h"
#include "Satellite.h"
#include "libsgp4/Tle.h"
#include "libsgp4/DateTime.h"
#include "libsgp4/Observer.h"
#include "libsgp4/Eci.h"
#include "libsgp4/CoordTopocentric.h"
#include <vector>
#include <string>
#include <math.h>
#include <cmath>

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
    if((tle.Inclination(true) > 0 && tle.Inclination(true) < 90) || (tle.MeanMotion() > 14 && tle.MeanMotion() < 17)) {
        return true;
    }
    return false;
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

void Satellite::assignRank() {
    auto distance = calculateDistance();
    auto mean_motion = tle.MeanMotion();
    auto elevation = this->geo.altitude;
    //auto angle_of_elevation = atan(elevation/distance); // arctan (elevation / distance)

    if (!isLEO()) {
        rank = 0; // satellite is tossed out when 0
    } else if (mean_motion >= 17 && maxElevation >= 60) {
        rank = 1;
    } else if ((15 <= mean_motion && mean_motion <= 16) && (30 <= maxElevation)) {
        rank = 2;
    } else if((10 <= maxElevation)) {
        rank = 3;
    } else {
        rank = 0;
    }
}

libsgp4::DateTime Satellite::getStartTime(){
    return startTime;
}

libsgp4::DateTime Satellite::getEndTime(){
    return endTime;
}

libsgp4::DateTime Satellite::setStartTime(libsgp4::DateTime st){
    startTime = st;
}

libsgp4::DateTime Satellite::setEndTime(libsgp4::DateTime et){
    endTime = et;
}

string Satellite::toString(){
    string satInfo = tle.Name();
    satInfo.append(" ");
    satInfo.append(startTime.ToString());
    satInfo.append(" ");
    satInfo.append(endTime.ToString());
    return satInfo;
}

void Satellite::generatePasses(){
    // Get current time
    libsgp4::DateTime now(dt);


// Loop over the next 24 hours
    const int numSteps = 24 * 60 * 60;
    std::vector<libsgp4::DateTime> times(numSteps);
    std::vector<libsgp4::CoordTopocentric> positions(numSteps);
    for (unsigned long i = 0; i < numSteps; ++i) {
        // Calculate time
        times[i] = now.AddSeconds((double)i);
        // Calculate satellite position
        libsgp4::Eci eciNext = sgp4.FindPosition(times[i]);
        libsgp4::CoordTopocentric topoC = obs.GetLookAngle(eciNext);
        // Save position
        positions[i] = topoC;
    }

    // libsgp4::DateTime visibility periods
    libsgp4::DateTime visibleStart, visibleEnd;
    bool visible = false;
    for (unsigned int i = 0; i < numSteps; ++i) {
        if (positions[i].elevation > 0) {
            if(maxElevation < positions[i].elevation){
                maxElevation = positions[i].elevation;
            }
            if (!visible) {
                visibleStart = times[i];
                visible = true;
            }
            visibleEnd = times[i];
        } else {
            if (visible) {
                std::pair access(visibleStart, visibleEnd);
                passes.push_back(access);
                //std::cout << "Satellite visible from " << visibleStart << " to " << visibleEnd << "\n";
                visible = false;
            }
        }
    }

    if (visible) {
        std::pair access(visibleStart, visibleEnd);
        passes.push_back(access);
        //std::cout << "Satellite visible from " << visibleStart << " to " << visibleEnd << "\n";
    }
    if(passes.size() > 0){
        startTime = passes.at(0).first;
        endTime = passes.at(0).second;
    }

}

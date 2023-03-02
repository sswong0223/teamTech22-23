//
// Created by Clarissa Mac on 2/28/23.
//

#ifndef TESTSGP4_SATELLITE_H
#define TESTSGP4_SATELLITE_H

#include "libsgp4/Tle.h"
#include "libsgp4/DateTime.h"
#include "libsgp4/Eci.h"
#include "libsgp4/SGP4.h"
#include "libsgp4/CoordTopocentric.h"
#include "libsgp4/CoordGeodetic.h"
#include "libsgp4/Observer.h"

using namespace std;

class Satellite {
    private:
        libsgp4::Tle tle;
        //duration that the satellite will communicate with the ground station
        libsgp4::SGP4 duration;
        libsgp4::DateTime dt;
        libsgp4::Eci eci;
        libsgp4::CoordTopocentric topo;
        libsgp4::CoordGeodetic geo;
        libsgp4::Observer obs;
        libsgp4::SGP4 sgp4;

    public:
        //constructor
        Satellite(libsgp4::TLE tle){
            this->tle = tle;
            sgp4(tle);
        }

        //function to calculate - Where and when the antenna should point over a 7-day period (coordinates,
        // angles as it changes over a 7-day period, take into account velocity of satellite moving)
        void calculatePos(float timePassed){
            dt = tle.Epoch().AddMinutes(timePassed);
            //calculate satellite position
            eci = sgp4.FindPosition(dt);
            //get look angle for observer to satellite
            topo = obs.GetLookAngle(eci);
            //convert satellite position to geodetic coordinates
            geo = eci.ToGeodetic();
        }

        float calculateDistance(){

        }

};

#endif //TESTSGP4_SATELLITE_H

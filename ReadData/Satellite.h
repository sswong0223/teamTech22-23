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
        //libsgp4::SGP4 duration;
        //start time?
        libsgp4::DateTime dt;
        libsgp4::Eci eci;
        libsgp4::CoordTopocentric topo;
        libsgp4::CoordGeodetic geo;
        libsgp4::Observer obs;
        libsgp4::SGP4 sgp4;
        int rank;

    public:
        //constructor
        //initialized some class object variables right when the constructor is built b/c most of them have no default constructor
        //change obs and eci inputs later as needed
        Satellite(libsgp4::Tle tle1): tle(tle1), sgp4(tle), obs(29,82,1), eci(dt, 1, 1, 1){
            //this->tle = tle1;
            //sgp4(tle);
            assignRank();
        }

        bool isLEO();

        //function to calculate - Where and when the antenna should point over a 7-day period (coordinates,
        // angles as it changes over a 7-day period, take into account velocity of satellite moving)
        void calculatePos(float timePassed);

        float calculateDistance();

        void assignRank();

        void toString();
};

#endif //TESTSGP4_SATELLITE_H

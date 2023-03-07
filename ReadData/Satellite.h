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

        float calculateDistance() {
            //need to code calculation for distance between ground station and satellite
            //ground station is 29°38'53.1"N 82°20'51.1"W on top of Weimer Hall
            //angle = arccos(point1 * point2)
            //distance = angle * pi * radius
        }

        void assignRank(){
            //need to code ranking system here (Aerospace team will hopefully provide this)
            //assign variable rank with ranking

        }

        void ToString(){
            //need to figure out what output needs to be outputted for each satellite in the 7-day schedule
            cout << eci << endl;
            cout << topo << endl;
            cout << geo << endl;
        }
};

#endif //TESTSGP4_SATELLITE_H

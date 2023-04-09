//
// Created by Clarissa Mac on 2/28/23.
//

#pragma once

#include <vector>
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
        // vector of start time end time pairs
        std::vector<std::pair<libsgp4::DateTime, libsgp4::DateTime>> passes;


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
        Satellite(libsgp4::Tle tle1, libsgp4::DateTime currentTime): tle(tle1), dt(currentTime), eci(dt, 1, 1, 1), obs(29,82,1), sgp4(tle){
            //this->tle = tle1;
            //sgp4(tle);
            // OBS: 29, 82, 1
            eci = sgp4.FindPosition(dt);
            geo = eci.ToGeodetic();
            assignRank();
            // calculate passes
        }

        bool isLEO();

        //function to calculate - Where and when the antenna should point over a 7-day period (coordinates,
        // angles as it changes over a 7-day period, take into account velocity of satellite moving)
        void calculatePos(float timePassed);

        float calculateDistance();

        void assignRank();


        void toString();

        int getRank(){
            return rank;
        }

        libsgp4::DateTime getEarliestEndTime() const{
            return passes.at(0).second;
        }

        //work on this after we know how endTime is formatted
        bool operator> (const Satellite& rSat) const{
            if(getEarliestEndTime().Compare(rSat.getEarliestEndTime()) == 1) //endTime > rSat.getEndTime()
                return true;
            else
                return false;
        }

        void generatePasses();

};

class satComparator{
public:
    int operator()(const Satellite& lSat, const Satellite& rSat){
        if(lSat.getEarliestEndTime().Compare(rSat.getEarliestEndTime()) == 1) //endTime > rSat.getEndTime()
            return true;
        else
            return false;

    }
};

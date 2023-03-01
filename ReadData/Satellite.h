//
// Created by Clarissa Mac on 2/28/23.
//

#ifndef TESTSGP4_SATELLITE_H
#define TESTSGP4_SATELLITE_H

#include "libsgp4/Tle.h"

class Satellite {
    private:
        TLE tle;
        //variable to help rank satellites priority
        int ranking;
        float durationAccess;

        //in addition to TLE variables, need variables detailing when and were the antenna should point

        //function to calculate - Where and when the antenna should point over a 7-day period (coordinates,
        // angles as it changes over a 7-day period, take into account velocity of satellite moving)
        string calculateSat(Satellite sat){
            /* We are working with LEO satellites...
             *
             * important values to consider:
             * - mean motion
             * - epoch year and julian day fraction
             * - eccentricity
             * - inclination
             * - right ascension of the ascension mode
             * - argument of perigee
             *  -revolution number at epoch and check sum
             *
             * Finding Coordinates:
             * Orbital Formula: r = (h2/μ)/(1 + e cos θ)
             * TLE converted to code: https://kaitlyn.guru/projects/two-line-elements-tle/
             *
             * Duration of Access: minimum (1-20 minutes) 7-15 is probably best
             * https://www.mathworks.com/help/satcom/ug/satellite-constellation-access-to-groundstation.html
             *
             * Aerospace team will determine ground station location, so right now focus on how you will calculate
             * where and when antenna will point, no need to fully implement and test, just brainstorm how your code
             * will be
             *
             * !!Use SPG4 reference sheet and look through libsgp4 library to find any functions that might help
             */
        }
    public:
        //constructor
        Satellite(TLE tle){
            this->tle = tle;
        }

        void printName();

        void addRanking(int n){
            ranking = n;
        }


};

#endif //TESTSGP4_SATELLITE_H

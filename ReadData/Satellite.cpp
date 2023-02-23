//
// Created by Rebecca Diaz on 2/20/23.
//

#include "Satellite.h"
#include <iostream>

Satellite::Satellite(std::string line1, std::string line2) : tle(line1, line2){

}

void Satellite::printName() {
    std::cout << tle.Name() << std::endl;
}

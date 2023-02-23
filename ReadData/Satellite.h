//
// Created by Rebecca Diaz on 2/20/23.
//

#pragma once
#include "libsgp4/Tle.h"


class Satellite {
    libsgp4::Tle tle;
public:
    Satellite(std::string line1, std::string line2);

    void printName();

};


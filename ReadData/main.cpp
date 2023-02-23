#include <iostream>
#include <vector>
#include <fstream>
#include "sgp4-master/libsgp4/SGP4.h"
#include "Satellite.h"

int main() {

    // Hard code test: delete later
    std::string line1 = "1 00900U 64063C   23046.50614910  .00001371  00000+0  14455-2 0  9991";
    std::string line2 = "2 00900  90.1810  45.4651 0027461  15.1398 149.1107 13.74104475904037";
    libsgp4::Tle obj1(line1, line2);
    std::cout << obj1.Name() << std::endl;

    // Initialize variables for reading input file
    std::string buffer;
    std::fstream input("active.txt"); // The file of satellites is found in the debug folder
    std::vector<Satellite> satellites;

    // Read in data from active.txt file until you reach the end of the file
    while(std::getline(input, buffer)){
        getline(input, line1);
        getline(input, line2);
        line1.pop_back(); // Gets rid of carriage return character
        line2.pop_back(); // Gets rid of carriage return character
        libsgp4::Tle tle1(line1, line2);
        Satellite satellite(line1, line2);
        satellites.push_back(satellite);
    }

    satellites.at(0).printName();

    return 0;
}

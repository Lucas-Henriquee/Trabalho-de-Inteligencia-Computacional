#ifndef AIRCRAFT_FUNCTIONS_HPP
#define AIRCRAFT_FUNCTIONS_HPP

#include "defines.hpp"
#include "Aircraft_Struct.hpp"

void readInstance(ifstream &instance, vector<Aircraft> &aircrafts);
void printAircrafts(vector<Aircraft> &aircrafts);
void verifySeparationConstraint(Aircraft i, Aircraft j);

#endif // AIRCRAFT_FUNCTIONS_HPP

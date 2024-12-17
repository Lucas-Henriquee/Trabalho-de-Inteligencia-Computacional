#ifndef SOLUTION_FUNCTIONS_HPP
#define SOLUTION_FUNCTIONS_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

void printSolution(Solution solution);
void constructInitialSolution(vector<Aircraft> aircrafts, Solution &solution);
void calculateObjectiveFunction(vector<Aircraft> aircrafts, Solution &solution);

#endif // SOLUTION_FUNCTIONS_HPP
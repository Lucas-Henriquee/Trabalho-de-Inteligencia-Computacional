#ifndef SOLUTION_FUNCTIONS_HPP
#define SOLUTION_FUNCTIONS_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

void printSolution(Solution &solution);
size_t calculateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution);
void updateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution);
Solution copySolution(Solution &solution);
bool viability_verifier(vector<Aircraft> &aircrafts, Solution &solution);

#endif // SOLUTION_FUNCTIONS_HPP
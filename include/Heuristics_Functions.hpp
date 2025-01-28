#ifndef HEURISTICS_FUNCTIONS_HPP
#define HEURISTICS_FUNCTIONS_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

Solution runConstructiveHeuristic(vector<Aircraft>& aircrafts);
Solution runILS(vector<Aircraft> aircrafts, Solution initial_solution, int max_iterations);
void applyLocalSearch(vector<Aircraft> aircrafts, Solution &solution);
void applyShiftLocalSearch(vector<Aircraft> aircrafts, Solution &solution);
Solution runILSWithRVND(vector<Aircraft> aircrafts, Solution initial_solution, int max_iterations, int max_ils_iterations);
void applyPerturbation(vector<Aircraft> &aircrafts, Solution &solution);
bool shiftNeighborhood(vector<Aircraft> &aircrafts, Solution &solution);
bool twoOptNeighborhood(vector<Aircraft> &aircrafts, Solution &solution);
bool swapNeighborhood(vector<Aircraft> &aircrafts, Solution &solution);


#endif // HEURISTICS_FUNCTIONS_HPP
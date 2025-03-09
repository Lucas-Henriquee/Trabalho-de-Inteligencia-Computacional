#ifndef POPUlATIONAL_STRATEGY_HPP
#define POPUlATIONAL_STRATEGY_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

void populationalStrategy(vector<Aircraft> &aircrafts, Solution &solution, size_t population_size, size_t generations);
void ACO(vector<Aircraft> &aircrafts, Solution &solution, size_t population_size, size_t generations);

#endif // POPUlATIONAL_STRATEGY_HPP
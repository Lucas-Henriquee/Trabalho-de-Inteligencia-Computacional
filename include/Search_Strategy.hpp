#ifndef SEARCH_STRATEGY_HPP
#define SEARCH_STRATEGY_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

void constructiveStrategy(vector<Aircraft> &aircrafts, Solution &solution);
void searchStrategy(vector<Aircraft> &aircrafts, Solution &solution);
void NEHConstructive(vector<Aircraft> &aircrafts, Solution &solution, vector<Aircraft> &destroyed_aircrafts);
void scheduleLandingTimes(vector<Aircraft> &aircrafts, Solution &solution);
void IG(vector<Aircraft> &aircrafts, Solution &solution);
void VND(vector<Aircraft> &aircrafts, Solution &solution);
bool applySwap(vector<Aircraft> &aircrafts, Solution &solution);
bool applyShift(vector<Aircraft> &aircrafts, Solution &solution);
bool applyRunwaySwap(vector<Aircraft> &aircrafts, Solution &solution);
vector<Aircraft> destroySolution(Solution &solution);
vector<Aircraft> destroySolutionRandomly(Solution &solution);
vector<Aircraft> destroyRunway(Solution &solution);

#endif // SEARCH_STRATEGY_HPP
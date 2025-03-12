#ifndef POPUlATIONAL_STRATEGY_HPP
#define POPUlATIONAL_STRATEGY_HPP

#include "defines.hpp"
#include "Solution_Struct.hpp"
#include "Aircraft_Struct.hpp"

void populationalStrategy(vector<Aircraft> &aircrafts, Solution &solution, size_t population_size, size_t generations);
void ACO(vector<Aircraft> &aircrafts, Solution &solution, size_t num_ants, size_t iterations);
void initializePheromones(vector<vector<double>> &pheromone, size_t num_aircrafts, double initial_pheromone, vector<Aircraft> &aircrafts);
void updatePheromone(vector<Solution> &solutions, vector<vector<double>> &pheromone, double evaporation_rate);
size_t chooseAircraft(vector<double> &probabilities, vector<Aircraft> &aircrafts, double exploration_rate);
bool isFeasibleInsertion(Runway_Schedule &runway, Aircraft &aircraft, Node *position);
void constructSolution(vector<Aircraft> &aircrafts, vector<vector<double>> &pheromone, size_t num_runways, double exploration_rate, Solution &solution);

#endif // POPUlATIONAL_STRATEGY_HPP
#ifndef SOLUTION_STRUCT_HPP
#define SOLUTION_STRUCT_HPP

#include "defines.hpp"
#include "Aircraft_Struct.hpp"
#include "Runway_Schedule.hpp"

struct Solution
{
    vector<Runway_Schedule> schedules;
    size_t objective_function = 0;
    size_t num_runways = 0;
    string heuristic = " ";
    double execution_time = 0.0;

    double initial_pheromone = 1.0;
    double evaporation_rate = 0.1;
    double pheromone_deposit = 1.0;
    double exploration_rate = 0.1;

    Solution(size_t num_runways) : num_runways(num_runways) {schedules.resize(num_runways);}
};

#endif // SOLUTION_STRUCT_HPP
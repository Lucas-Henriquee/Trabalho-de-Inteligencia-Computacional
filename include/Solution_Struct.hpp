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

    Solution(size_t num_runways) : num_runways(num_runways) {schedules.resize(num_runways);}
};

#endif // SOLUTION_STRUCT_HPP
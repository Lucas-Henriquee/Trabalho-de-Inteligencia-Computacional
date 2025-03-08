#ifndef SOLUTION_STRUCT_HPP
#define SOLUTION_STRUCT_HPP

#include "defines.hpp"
#include "Aircraft_Struct.hpp"
#include "Runway_Schedule.hpp"

struct Solution
{
    Runway_Schedule schedule;
    size_t objective_function = 0;
};

#endif // SOLUTION_STRUCT_HPP
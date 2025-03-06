#ifndef SOLUTION_STRUCT_HPP
#define SOLUTION_STRUCT_HPP

#include "defines.hpp"
#include "Aircraft_Struct.hpp"
#include "RunwaySchedule.hpp"

struct Solution
{
    RunwaySchedule schedule;
    size_t objective_function = 0;
};

#endif // SOLUTION_STRUCT_HPP
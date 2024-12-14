#ifndef AIRCRAFT_STRUCT_HPP
#define AIRCRAFT_STRUCT_HPP

#include "defines.hpp"

struct Aircraft
{
    int appearance_time;
    int earliest_time;
    int target_time;
    int latest_time;
    float penalty_before;
    float penalty_after;
    vector<int> separation_times;
};

#endif // AIRCRAFT_STRUCT_HPP
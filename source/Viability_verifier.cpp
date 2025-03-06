#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"

bool viability_verifier(vector<Aircraft> aircrafts, Solution solution)
{
    size_t error_counter = 0;
    Node *current = solution.schedule.getHead();

    while (current != nullptr)
    {
        int aircraft_id = current->aircraft.plane_index;
        int solution_time = current->landing_time;
        int earliest_time = aircrafts[aircraft_id - 1].earliest_time;
        int latest_time = aircrafts[aircraft_id - 1].latest_time;

        if (solution_time < earliest_time || solution_time > latest_time)
            error_counter++;

        if (current->prev != nullptr)
        {
            int previous_aircraft_id = current->prev->aircraft.plane_index;
            int previous_landing_time = current->prev->landing_time;
            int separation_time = aircrafts[aircraft_id - 1].separation_times[previous_aircraft_id - 1];

            if (previous_landing_time + separation_time > solution_time)
                error_counter++;
        }

        current = current->next;
    }

    return (error_counter == 0);
}
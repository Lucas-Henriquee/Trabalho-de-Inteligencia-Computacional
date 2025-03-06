#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/Viability_Verifier.hpp"
#include <unistd.h>

void printSolution(Solution &constructive, Solution &ils, Solution &ils_rvnd)
{
    cout << "----------------------------------" << endl;
    cout << "Função Objetivo:" << endl;
    cout << "Heurística Construtiva: " << constructive.objective_function << endl;
    cout << "ILS: " << ils.objective_function << endl;
    cout << "ILS com RVND: " << ils_rvnd.objective_function << endl;
    cout << "----------------------------------" << endl;
}

size_t calculateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    size_t objective_function = 0;
    Node *current = solution.schedule.getHead();

    while (current != nullptr)
    {
        int aircraft_id = current->aircraft.plane_index;
        int aircraft_time = current->landing_time;
        int difference = aircrafts[aircraft_id - 1].target_time - aircraft_time;

        if (difference < 0)
            objective_function += abs(difference) * aircrafts[aircraft_id - 1].penalty_after;
        else
            objective_function += difference * aircrafts[aircraft_id - 1].penalty_before;

        current = current->next;
    }

    return objective_function;
}

void constructInitialSolution(vector<Aircraft> aircrafts, Solution &solution)
{
    sortAircraftsbyEarliestTime(aircrafts);

    solution.schedule.push_back(aircrafts[0], aircrafts[0].target_time);

    for (size_t i = 1; i < aircrafts.size(); i++)
    {
        int previous_landing_time = solution.schedule.getTail()->landing_time;
        int separation_time = aircrafts[i].separation_times[aircrafts[i - 1].plane_index];
        int landing_time = max(aircrafts[i].earliest_time, previous_landing_time + separation_time);

        solution.schedule.push_back(aircrafts[i], landing_time);
    }

    updateObjectiveFunction(aircrafts, solution);
}

void updateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    solution.objective_function = calculateObjectiveFunction(aircrafts, solution);
}

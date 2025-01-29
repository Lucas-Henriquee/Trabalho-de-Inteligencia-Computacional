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
    size_t num_aircrafts=solution.aircraft_sequence.size();
    size_t objective_function=0;
    for (size_t i = 0; i < num_aircrafts; i++)
    {
        size_t aircraft_id=solution.aircraft_sequence[i].first.plane_index;
        size_t aircraft_index=aircraft_id-1;
        size_t aircraft_time=solution.aircraft_sequence[i].second;
        int difference = aircrafts[aircraft_index].target_time-aircraft_time;
        if (difference<0)
            objective_function+=abs(difference) * aircrafts[aircraft_index].penalty_after;
        else
            objective_function+=difference * aircrafts[aircraft_index].penalty_before;
    }

    return objective_function;
}

void constructInitialSolution(vector<Aircraft> aircrafts, Solution &solution)
{
    size_t num_aircrafts=aircrafts.size();

    sortAircraftsbyEarliestTime(aircrafts);

    solution.aircraft_sequence.push_back(make_pair(aircrafts[0],aircrafts[0].target_time));

    for (size_t i = 1; i < num_aircrafts; i++)
    {
        solution.aircraft_sequence.push_back(make_pair(aircrafts[i], max(aircrafts[i].earliest_time, (solution.aircraft_sequence[i-1].second + aircrafts[i].separation_times[i-1]))));
    }

    updateObjectiveFunction(aircrafts, solution);
}

void updateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    solution.objective_function = calculateObjectiveFunction(aircrafts, solution);
}


#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/Viability_Verifier.hpp"
#include <unistd.h>

void printSolution(Solution &solution)
{
    cout << "----------------------------------" << endl;
    cout << "Função Objetivo:" << endl;
    cout << "Heurística Implementada: " << solution.objective_function << endl;
    cout << "----------------------------------" << endl;
}

size_t calculateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    size_t objective_function = 0;
    Node *current = solution.schedule.getHead();

    bool viable = viability_verifier(aircrafts, solution);
    if(!viable){
        return static_cast<size_t>(-1);
    }

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

void updateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    solution.objective_function = calculateObjectiveFunction(aircrafts, solution);
}

Solution copySolution(Solution &solution)
{
    Solution new_solution;
    Node *current = solution.schedule.getHead();

    while (current != nullptr)
    {
        new_solution.schedule.push_back(current->aircraft, current->landing_time);
        current = current->next;
    }

    new_solution.objective_function = solution.objective_function;

    return new_solution;
}

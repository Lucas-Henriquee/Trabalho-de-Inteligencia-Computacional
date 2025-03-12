#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"

void printSolution(vector<Aircraft> &aircrafts, Solution &solution)
{
    cerr<<"Socorro"<<endl;
    cout << "----------------------------------" << endl;
    cout << "Função Objetivo: " << solution.heuristic << endl;
    cout << "Heurística Implementada: " << solution.objective_function << endl;
    cout << "Validade da Solução: " << (viability_verifier(aircrafts, solution) ? "Válida" : "Inválida") << endl;
    cout << "----------------------------------" << endl;
}

size_t calculateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    size_t objective_function = 0;

    bool viable = viability_verifier(aircrafts, solution);

    if (!viable)
        return static_cast<size_t>(-1);

    for (size_t r = 0; r < solution.schedules.size(); r++) 
    {
        Node *current = solution.schedules[r].getHead();

        while (current)
        {
            int aircraft_id = current->aircraft.plane_index;
            int aircraft_time = current->landing_time;
            int difference = aircrafts[aircraft_id].target_time - aircraft_time;

            if (difference < 0)
                objective_function += abs(difference) * aircrafts[aircraft_id].penalty_after;

            else
                objective_function += difference * aircrafts[aircraft_id].penalty_before;

            current = current->next;
        }
    }

    return objective_function;
}

void updateObjectiveFunction(vector<Aircraft> &aircrafts, Solution &solution)
{
    solution.objective_function = calculateObjectiveFunction(aircrafts, solution);
}

Solution copySolution(Solution &solution)
{
    Solution new_solution(solution.num_runways); 

    for (size_t r = 0; r < solution.schedules.size(); r++)
    {
        Node *current = solution.schedules[r].getHead();
        while (current != nullptr)
        {
            new_solution.schedules[r].push_back(current->aircraft, current->landing_time);
            current = current->next;
        }
    }

    new_solution.objective_function = solution.objective_function;
    return new_solution;
}

void copySolution(Solution source, Solution &target)
{
    target.num_runways = source.num_runways;
    target.objective_function = source.objective_function;
    for (size_t r = 0; r < target.schedules.size(); r++)
    {
        Node *current = target.schedules[r].getHead();
        while (current != nullptr)
        {
            Node *next = current->next;
            target.schedules[r].remove(current);
            current = next;
        }
    }

    for (size_t r = 0; r < source.schedules.size(); r++)
    {
        Node *current = source.schedules[r].getHead();
        while (current != nullptr)
        {
            target.schedules[r].push_back(current->aircraft, current->landing_time);
            current = current->next;
        }
    }
}

bool viability_verifier(vector<Aircraft> &aircrafts, Solution &solution)
{
    size_t error_counter = 0;

    for (size_t r = 0; r < solution.schedules.size(); r++) 
    {
        Node *current = solution.schedules[r].getHead();
        while (current != nullptr)
        {
            int aircraft_id = current->aircraft.plane_index;
            int solution_time = current->landing_time;
            int earliest_time = aircrafts[aircraft_id].earliest_time;
            int latest_time = aircrafts[aircraft_id].latest_time;

            if (solution_time < earliest_time || solution_time > latest_time)
                error_counter++;

            if (current->prev != nullptr)
            {
                int previous_aircraft_id = current->prev->aircraft.plane_index;
                int previous_landing_time = current->prev->landing_time;
                int separation_time = aircrafts[aircraft_id].separation_times[previous_aircraft_id];

                if (previous_landing_time + separation_time > solution_time)
                    error_counter++;
            }

            current = current->next;
        }
    }

    return (error_counter == 0);
}
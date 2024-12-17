#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include <unistd.h>


void printSolution(Solution solution)
{
      size_t num_aircrafts=solution.aircraft_sequence.size();
      cout<<"Solucao da instancia com "<<num_aircrafts<<" aeronaves:"<<endl<<endl;
      cout<<"Indice da aeronave / tempo de pouso: "<<endl;
      for (size_t i = 0; i < num_aircrafts; i++)
      {
          cout<<solution.aircraft_sequence[i].first + 1<<" / ";
          cout<<solution.aircraft_sequence[i].second<<endl;
      }
      cout<< "Função objetivo: " << solution.objective_function << endl;
      cout<<endl<<endl;
}

void calculateObjectiveFunction(vector<Aircraft> aircrafts, Solution &solution)
{
    size_t num_aircrafts=solution.aircraft_sequence.size();
    size_t objective_function=0;
    for (size_t i = 0; i < num_aircrafts; i++)
    {
        size_t aircraft_id=solution.aircraft_sequence[i].first;
        size_t aircraft_index=aircraft_id-1;
        size_t aircraft_time=solution.aircraft_sequence[i].second;
        int difference = aircrafts[aircraft_index].target_time-aircraft_time;
        if (difference<0)
            objective_function+=abs(difference) * aircrafts[aircraft_index].penalty_after;
        else
            objective_function+=difference * aircrafts[aircraft_index].penalty_before;
    }
    solution.objective_function=objective_function;
}

void constructInitialSolution(vector<Aircraft> aircrafts, Solution &solution)
{
    size_t num_aircrafts=aircrafts.size();

    sortAircraftsbyTargetTime(aircrafts);

    solution.aircraft_sequence.push_back(make_pair(aircrafts[0].plane_index,aircrafts[0].target_time));

    for (size_t i = 1; i < num_aircrafts; i++)
    {
        solution.aircraft_sequence.push_back(make_pair(aircrafts[i].plane_index, max(aircrafts[i].target_time, (solution.aircraft_sequence[i-1].second + aircrafts[i].separation_times[i-1]))));
    }
}
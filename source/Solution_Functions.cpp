#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"


void printSolution(Solution solution)
{
      size_t num_aircrafts=solution.aircraft_sequence.size();
      cout<<"Solucao da instancia com "<<num_aircrafts<<" aeronaves:"<<endl<<endl;
      cout<<"Indice da aeronave / tempo de pouso: "<<endl;
      for (size_t i = 0; i < num_aircrafts; i++)
      {
          cout<<solution.aircraft_sequence[i]<<" / ";
          cout<<solution.landing_times[i]<<endl;
      }
      cout<<endl<<endl;
  }
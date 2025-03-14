#include "include/Aircraft_Struct.hpp"
#include "include/Aircraft_Functions.hpp"
#include "include/defines.hpp"
#include "include/Solution_Struct.hpp"
#include "include/Solution_Functions.hpp"
#include "include/Search_Strategy.hpp"
#include "include/Populational_Strategy.hpp"

int main(int argc, char *argv[])
{

    // argv[1] arquivo de entrada
    // argv[2] quantidade de pistas (em breve será implemtada :) )

    if (argc != 0)
    {

        string filename = argv[1];
        int num_runways = stoi(argv[2]);

        ifstream file(filename);


        if (file.is_open())
        {
            vector<Aircraft> aircrafts;
            readInstance(file, aircrafts);

            Solution constructive_solution(num_runways);
            constructiveStrategy(aircrafts, constructive_solution);

            Solution search_solution(num_runways);
            searchStrategy(aircrafts, search_solution);

            // Solution populational_solution(num_runways);
            // populational_solution.initial_pheromone = 1.0;
            // populational_solution.evaporation_rate = 0.1;
            // populational_solution.pheromone_deposit = 1.0;
            // populational_solution.exploration_rate = 0.1;
            // populationalStrategy(aircrafts, populational_solution, 100, 1000);

            file.close();
        }
        else
            cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
#include "include/Aircraft_Struct.hpp"
#include "include/Aircraft_Functions.hpp"
#include "include/defines.hpp"
#include "include/Solution_Struct.hpp"
#include "include/Solution_Functions.hpp"
#include "include/Viability_Verifier.hpp"
#include "include/Heuristics_Functions.hpp"

int main(int argc, char *argv[])
{

    // argv[1] arquivo de entrada
    // argv[2] quantidade de pistas (em breve será implemtada :) )

    if (argc != 0)
    {

        string filename = argv[1];

        ifstream file(filename);

        if (file.is_open())
        {
            vector<Aircraft> aircrafts;
            readInstance(file, aircrafts);
            //printAircrafts(aircrafts);

            Solution constructive_solution = runConstructiveHeuristic(aircrafts);

            Solution ils_solution = runILS(aircrafts, constructive_solution, 1000);

            // Solution ils_rvnd_solution = runILSWithRVND(aircrafts, constructive_solution, 1000, 50);
            Solution ils_rvnd_solution;

            // printSolution(constructive_solution, ils_solution, ils_rvnd_solution);

            printSolution(constructive_solution, ils_solution, ils_rvnd_solution);

            file.close();
        }
        else
            cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
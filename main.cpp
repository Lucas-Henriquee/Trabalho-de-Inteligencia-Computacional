#include "include/Aircraft_Struct.hpp"
#include "include/Aircraft_Functions.hpp"
#include "include/defines.hpp"
#include "include/Solution_Struct.hpp"
#include "include/Solution_Functions.hpp"
#include "include/Viability_Verifier.hpp"

int main(int argc, char *argv[])
{

    // argv[1] arquivo de entrada

    if (argc != 0)
    {

        string filename = argv[1];

        ifstream file(filename);

        if (file.is_open())
        {
            vector<Aircraft> aircrafts;
            readInstance(file, aircrafts);
            printAircrafts(aircrafts);

            Solution solution;
            solution.aircraft_sequence={1,2,3,4,5,6,7,8,9,10};
            solution.landing_times={5,10,12,14,16,18,20,30,40,55};
            printSolution(solution);

            Solution solution1=Solution_to_airland1();
            viability_verifier(aircrafts,solution1);

            file.close();
        }
        else
            cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
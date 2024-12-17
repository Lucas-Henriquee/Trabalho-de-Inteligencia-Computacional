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

            //Testar solução
            //Solution solution=
            //printSolution(solution);
            //viability_verifier(aircrafts,solution);

            file.close();
        }
        else
            cout << "Erro ao abrir o arquivo" << endl;
    }

    return 0;
}
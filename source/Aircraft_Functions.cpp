#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"

void readInstance(ifstream &instance, vector<Aircraft> &aircrafts)
{
    string line;

    int num_aircrafts, discard;

    if (getline(instance, line))
    {
        istringstream iss(line);
        iss >> num_aircrafts >> discard;
    }

    for (int i = 0; i < num_aircrafts; i++)
    {
        Aircraft aircraft;

        if (getline(instance, line))
        {
            istringstream iss(line);
            iss >> aircraft.appearance_time >> aircraft.earliest_time >> aircraft.target_time >> aircraft.latest_time >> aircraft.penalty_before >> aircraft.penalty_after;
        }

        while (static_cast<int>(aircraft.separation_times.size()) < num_aircrafts && getline(instance, line))
        {
            istringstream iss(line);
            int time;

            while (iss >> time)
            {
                aircraft.separation_times.push_back(time);
                if (static_cast<int>(aircraft.separation_times.size()) == num_aircrafts)
                    break;
            }
        }

        aircrafts.push_back(aircraft);
    }
}

void printAircrafts(vector<Aircraft> &aircrafts)
{
    cout << "Dados das " << aircrafts.size() << " aeronaves:\n\n";
    for (size_t i = 0; i < aircrafts.size(); i++)
    {
        cout << "Aircraft " << i + 1 << endl;
        cout << "Appearance Time: " << aircrafts[i].appearance_time;
        cout << "\t Earliest Time: " << aircrafts[i].earliest_time;
        cout << "\t Target Time: " << aircrafts[i].target_time;
        cout << "\t Latest Time: " << aircrafts[i].latest_time << endl;
        cout << "Penalty Before: " << aircrafts[i].penalty_before;
        cout << "\t Penalty After: " << aircrafts[i].penalty_after << endl;
        cout << "Separation Times: ";

        for (size_t j = 0; j < aircrafts[i].separation_times.size(); j++)
            cout << aircrafts[i].separation_times[j] << " ";

        cout << "\n-------------------------------------------------------------------" << endl;
    }
}

//Prototipo de funcao q verifica a ordem de pouso de um par de avioes
void verifySeparationConstraint(Aircraft i, Aircraft j)
{
    int i_plane_index=i.plane_index;
    int j_plane_index=j.plane_index;
    int ijSeparationTime=j.separation_times[i_plane_index];
    int jiSeparationTime=i.separation_times[j_plane_index];

    if(i.latest_time<j.earliest_time)
    {
        if(i.latest_time+ijSeparationTime<=j.earliest_time)
        {
            //i sempre vai pousar antes de j e condição de separacão é
            //satisfeita automaticamente
        }

        if(i.latest_time+ijSeparationTime>j.earliest_time)
        {
            //i sempre vai pousar antes de j mas condição de separação
            //deve ser verificada
        }
    }
    if(j.latest_time<i.earliest_time)
    {
        if(j.latest_time+jiSeparationTime<=i.earliest_time)
        {
            //j sempre vai pousar antes de i e condição de separacão é
            //satisfeita automaticamente
        }

        if(j.latest_time+jiSeparationTime>i.earliest_time)
        {
            //j sempre vai pousar antes de i mas condição de separação
            //deve ser verificada
        }
    }
    else
    {
        //A ordem de pouso de i e j é incerta
    }

}
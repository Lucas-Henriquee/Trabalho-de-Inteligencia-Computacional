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

        aircraft.plane_index = i;

        if (getline(instance, line))
        {
            istringstream iss(line);
            iss >> discard >> aircraft.earliest_time >> aircraft.target_time >> aircraft.latest_time >> aircraft.penalty_before >> aircraft.penalty_after;
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
        cout << "Aircraft " << aircrafts[i].plane_index + 1 << endl;
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

void sortAircraftsbyTargetTime(vector<Aircraft> &aircrafts)
{
    // Sort aircrafts by target_time
    sort(aircrafts.begin(), aircrafts.end(), [](const Aircraft &a, const Aircraft &b) {
        return a.target_time < b.target_time;
    });

    // Reassign separate times to match the new order
    for (size_t i = 0; i < aircrafts.size(); i++)
    {
        vector<int> new_separation_times;
        for (size_t j = 0; j < aircrafts.size(); j++)
            new_separation_times.push_back(aircrafts[i].separation_times[aircrafts[j].plane_index]);
        aircrafts[i].separation_times = new_separation_times;
    }
}
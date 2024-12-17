#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"


//A testar
void viability_verifier(vector<Aircraft> aircrafts, Solution solution)
{
    cout<<"Verificador de viabilidade da solucao:"<<endl;
    cout << "\n-------------------------------------------------------------------" << endl;

    size_t num_aircrafts=aircrafts.size();

    for (size_t i=0; i<num_aircrafts; i++)
    {
        int current_aircraft_id=solution.aircraft_sequence[i];
        int current_aircraft_index=current_aircraft_id-1;
        int solution_time=solution.landing_times[i];
        int current_aircraft_earliest_time=aircrafts[current_aircraft_index].earliest_time;
        int current_aircraft_latest_time=aircrafts[current_aircraft_index].latest_time;
        
        //Se o tempo de solução for menor que o possível
        if(solution_time<current_aircraft_earliest_time)
        {
            //cout<<"i="<<i<<endl;
            //cout<<"id="<<current_aircraft_id<<endl;
            cout<<"Tempo da aeronave "<<current_aircraft_id<<" definido mais cedo que o possivel"<<endl;
            cout<<"Tempo minimo: "<<current_aircraft_earliest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;
        }

        //Se o tempo de solução for maior que o possível
        if(solution_time>current_aircraft_latest_time)
        {
            //cout<<"i="<<i<<endl;
            //cout<<"id="<<current_aircraft_id<<endl;
            cout<<"Tempo da aeronave "<<current_aircraft_id<<" definido mais tarde que o possivel"<<endl;
            cout<<"Tempo maximo: "<<current_aircraft_latest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;
        }

        //Se o tempo de solução não atender ao tempo de separação da aeronave anterior
        if(i!=0)
        {
            int previous_aircraft_id=solution.aircraft_sequence[i-1];
            int previous_aircraft_index=previous_aircraft_id-1;
            int previous_aircraft_solution_time=solution.landing_times[i-1];
            int separation_time=aircrafts[current_aircraft_index].separation_times[previous_aircraft_index];

            if(previous_aircraft_solution_time+separation_time>solution_time)
            {
                // cout<<"i="<<i<<endl;
                // cout<<"current id="<<current_aircraft_id<<endl;
                // cout<<"i-1="<<i-1<<endl;
                // cout<<"previous id="<<previous_aircraft_id<<endl;
                cout<<"Tempo da aeronave "<<current_aircraft_id<<" nao respeita o tempo de separacao da aeronave anterior " <<previous_aircraft_id<<endl;
                cout<<"Tempo da aeronave "<<previous_aircraft_id<<": "<<previous_aircraft_solution_time<<endl;
                cout<<"Tempo de separacao: "<<separation_time<<endl;
                cout<<"Tempo da aeronave "<<current_aircraft_id<<" : "<<solution_time<<endl;
                cout<<"Aeronave "<<current_aircraft_id<<" esta antecipada em "<<previous_aircraft_solution_time+separation_time-solution_time<<endl<<endl;
            }
        }
    }

    cout << "\n-------------------------------------------------------------------" << endl;
}

Solution Solution_to_airland1()
{
    Solution solution;
    solution.aircraft_sequence={3,4,5,1,8,6,7,9,10,2};
    solution.landing_times={80,521,555,559,573,576,577,591,657,774};
    solution.total_penalty=0;
     return solution;
}
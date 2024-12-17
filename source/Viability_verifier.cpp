#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"


//A testar
void viability_verifier(vector<Aircraft> aircrafts, Solution solution)
{
    cout<<"Verificador de viabilidade da solucao:"<<endl;
    cout << "\n-------------------------------------------------------------------" << endl;

    size_t error_counter=0;

    size_t num_aircrafts=aircrafts.size();

    for (size_t i=0; i<num_aircrafts; i++)
    {
        int current_aircraft_id=solution.aircraft_sequence[i].first;
        int solution_time=solution.aircraft_sequence[i].second;
        int current_aircraft_earliest_time=aircrafts[current_aircraft_id].earliest_time;
        int current_aircraft_latest_time=aircrafts[current_aircraft_id].latest_time;
        
        //Se o tempo de solução for menor que o possível
        if(solution_time<current_aircraft_earliest_time)
        {
            cout<<"i="<<i<<endl;
            cout<<"id="<<current_aircraft_id<<endl;
            cout<<"Tempo da aeronave "<<current_aircraft_id+1<<" definido mais cedo que o possivel"<<endl;
            cout<<"Tempo minimo: "<<current_aircraft_earliest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;

            error_counter++;
        }

        //Se o tempo de solução for maior que o possível
        if(solution_time>current_aircraft_latest_time)
        {
            cout<<"i="<<i<<endl;
            cout<<"id="<<current_aircraft_id<<endl;
            cout<<"Tempo da aeronave "<<current_aircraft_id+1<<" definido mais tarde que o possivel"<<endl;
            cout<<"Tempo maximo: "<<current_aircraft_latest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;
            
            error_counter++;
        }

        //Se o tempo de solução não atender ao tempo de separação da aeronave anterior
        if(i!=0)
        {
            int previous_aircraft_id=solution.aircraft_sequence[i-1].first;
            int previous_aircraft_solution_time=solution.aircraft_sequence[i-1].second;
            int separation_time=aircrafts[current_aircraft_id].separation_times[previous_aircraft_id];

            if(previous_aircraft_solution_time+separation_time>solution_time)
            {
                cout<<"i="<<i<<endl;
                cout<<"current id="<<current_aircraft_id<<endl;
                cout<<"i-1="<<i-1<<endl;
                cout<<"previous id="<<previous_aircraft_id<<endl;
                cout<<"Tempo da aeronave "<<current_aircraft_id+1<<" nao respeita o tempo de separacao da aeronave anterior " <<previous_aircraft_id+1<<endl;
                cout<<"Tempo da aeronave "<<previous_aircraft_id+1<<": "<<previous_aircraft_solution_time<<endl;
                cout<<"Tempo de separacao: "<<separation_time<<endl;
                cout<<"Tempo da aeronave "<<current_aircraft_id+1<<" : "<<solution_time<<endl;
                cout<<"Aeronave "<<current_aircraft_id+1<<" esta antecipada em "<<previous_aircraft_solution_time+separation_time-solution_time<<endl<<endl;
                
                error_counter++;
            }
        }
    }

    if(error_counter==0)
    {
        cout<<"Solucao viavel"<<endl;
    }

    cout << "\n-------------------------------------------------------------------" << endl;
}

Solution Solution_to_airland1()
{
    Solution solution;
    solution.aircraft_sequence={{2,80},{3,521},{4,555},{0,559},{7,573},{5,576},{6,577},{8,591},{9,657},{1,774}};
    solution.objective_function=0;
     return solution;
}
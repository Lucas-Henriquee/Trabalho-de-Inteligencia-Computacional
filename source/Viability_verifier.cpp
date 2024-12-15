#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"
#include "../include/Solution_Struct.hpp"


//A testar
void viability_verifier(vector<Aircraft> aircrafts, Solution solution)
{
    int num_aircrafts=aircrafts.size();
    

    for (int i=0; i<num_aircrafts; i++)
    {
        int current_aircract_index=solution.aircraft_sequence[i];
        int solution_time=solution.landing_times[i];
        int current_aircraft_earliest_time=aircrafts[current_aircract_index].earliest_time;
        int current_aircraft_latest_time=aircrafts[current_aircract_index].latest_time;
        int previous_aircraft_index=solution.aircraft_sequence[i-1];
        int previous_aircraft_solution_time=solution.landing_times[i-1];
        int separation_time=aircrafts[current_aircract_index].separation_times[previous_aircraft_index];
        
        //Se o tempo de solução for menor que o possível
        if(solution_time<current_aircraft_earliest_time)
            cout<<"Tempo da aeronave "<<current_aircract_index<<" definido mais cedo que o possível"<<endl;
            cout<<"Tempo mínimo: "<<current_aircraft_earliest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;
        
        //Se o tempo de solução for maior que o possível
        if(solution_time>current_aircraft_latest_time)
            cout<<"Tempo da aeronave "<<current_aircract_index<<" definido mais tarde que o possível"<<endl;
            cout<<"Tempo máximo: "<<current_aircraft_latest_time<<endl;
            cout<<"Tempo encontrado: "<<solution_time<<endl<<endl;
        
        //Se o tempo de solução não atender ao tempo de separação da aeronave anterior
        if(i!=0 && previous_aircraft_solution_time+separation_time>solution_time)
            cout<<"Tempo da aeronave "<<current_aircract_index<<" não respeita o tempo de separação da aeronave anterior " <<previous_aircraft_index<<endl;
            cout<<"Tempo da aeronave "<<previous_aircraft_index<<" : "<<previous_aircraft_solution_time<<endl;
            cout<<"Tempo de separação: "<<separation_time<<endl;
            cout<<"Tempo da aeronave "<<current_aircract_index<<" :"<<solution_time<<endl;
            cout<<"Aeronave "<<current_aircract_index<<" está antecipada em "<<previous_aircraft_solution_time+separation_time-solution_time<<endl<<endl;
    }
}
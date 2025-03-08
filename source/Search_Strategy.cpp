#include "../include/Search_Strategy.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"

using namespace std;

void searchStrategy(vector<Aircraft> &aircrafts, Solution &solution)
{
    IG(aircrafts, solution);
    printSolution(solution);
}

void IG(vector<Aircraft> &aircrafts, Solution &solution)
{
    vector<Aircraft> destroyed_aircrafts;
    copy(aircrafts.begin(), aircrafts.end(), back_inserter(destroyed_aircrafts));
    NEHConstructive(destroyed_aircrafts, solution, destroyed_aircrafts);
    Solution best_solution = copySolution(solution);
    bool improved = false;
    size_t non_improving = 0;
    do{
        VND(aircrafts, solution);
        if(solution.objective_function < best_solution.objective_function){
            //TODO: Deletar a melhor solução anterior
            best_solution = copySolution(solution);
            improved = true;
            non_improving = 0;
        }
        destroyed_aircrafts = destroySolution(solution);
        NEHConstructive(destroyed_aircrafts, solution, destroyed_aircrafts);
        if(improved){
            improved = false;
            non_improving++;
        }
    }while(non_improving < 100);
}

void NEHConstructive(vector<Aircraft> &aircrafts, Solution &solution, vector<Aircraft> &destroyed_aircrafts)
{
    //TODO: Implementar o NEH
    if(destroyed_aircrafts.size() == 0){
        return;
    }

    if(solution.schedule.getSize() == 0){
        solution.schedule.push_back(destroyed_aircrafts[0], destroyed_aircrafts[0].target_time);
    }

    for (size_t i = 1; i < destroyed_aircrafts.size(); i++)
    {
        Node *best = solution.schedule.getHead();
        for(size_t j = 0; j < solution.schedule.getSize(); j++){
            Node *current = solution.schedule.getHead();
            for (size_t k = 0; k < j; k++)
            {
                current = current->next;
            }
            //TODO: Verificar antes de inserir se aquela posição é válida
            solution.schedule.insert(current, destroyed_aircrafts[i], destroyed_aircrafts[i].target_time);
            updateObjectiveFunction(aircrafts, solution);
            if(current != nullptr){
                solution.schedule.remove(current->prev);
            }
            else{
                solution.schedule.remove(solution.schedule.getTail());
            }
            //TODO: Descobrir qual é a melhor posição para o avião através da função objetivo
        }
        //TODO: Inserir o avião na melhor posição
        solution.schedule.insert(best, aircrafts[i], aircrafts[i].target_time);
    }

    updateObjectiveFunction(aircrafts, solution);
}

vector<Aircraft> destroySolution(Solution &solution)
{
    vector<Aircraft> destroyed_aircrafts;
    int random = rand() % 100;
    if (random < 95)
    {
        destroyed_aircrafts = destroySolutionRandomly(solution);
    }
    else
    {
        destroyed_aircrafts = destroyRunway(solution);
    }
    return destroyed_aircrafts;
}

vector<Aircraft> destroySolutionRandomly(Solution &solution)
{
    vector<Aircraft> destroyed_aircrafts;
    int num_destroyed_aircrafts = rand() % int(ceil(solution.schedule.getSize()/10.0));
    for (size_t i = 0; i < num_destroyed_aircrafts; i++)
    {
        int random = rand() % solution.schedule.getSize();
        Node *current = solution.schedule.getHead();
        for (size_t j = 0; j < random; j++)
        {
            current = current->next;
        }
        destroyed_aircrafts.push_back(current->aircraft);
        solution.schedule.remove(current);
    }
    return destroyed_aircrafts;
}

vector<Aircraft> destroyRunway(Solution &solution)
{
    vector<Aircraft> destroyed_aircrafts;
    //TODO: Implementar a destruição de uma pista quando tiver mais de uma
    return destroyed_aircrafts;
}

void VND(vector<Aircraft> &aircrafts, Solution &solution)
{
    //TODO: Implementar o VND
    return;
}
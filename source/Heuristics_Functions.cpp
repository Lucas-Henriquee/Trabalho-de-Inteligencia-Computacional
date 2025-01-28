#include "../include/Heuristics_Functions.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Viability_Verifier.hpp"
#include "../include/defines.hpp"

Solution runConstructiveHeuristic(vector<Aircraft> aircrafts)
{
    Solution solution;

    constructInitialSolution(aircrafts, solution);

    if (!viability_verifier(aircrafts, solution))
        cout << "Solução inicial é inviável. Ajuste necessário." << endl;

    updateObjectiveFunction(aircrafts, solution);

    return solution;
}

Solution runILS(vector<Aircraft> aircrafts, Solution solution, int max_iterations)
{
    for (int i = 0; i < max_iterations; i++)
    {
        Solution perturbed_solution = solution;

        // Aplica uma perturbação para sair de ótimos locais
        applyPerturbation(aircrafts, perturbed_solution);

        // Aplica busca local padrao com RVND
        applyShiftLocalSearch(aircrafts, perturbed_solution);

        // Aceita a nova solução se for melhor
        if (calculateObjectiveFunction(aircrafts, perturbed_solution) < calculateObjectiveFunction(aircrafts, solution))
        {
            i = 0;
            solution = perturbed_solution;
        }
    }

    return solution;
}

void applyLocalSearch(vector<Aircraft> aircrafts, Solution &solution)
{
    vector<pair<function<bool(vector<Aircraft> &, Solution &)>, int>> neighborhoods = {
        {shiftNeighborhood, 0},
        {swapNeighborhood, 0},
        {twoOptNeighborhood, 0}};

    bool improved = true;

    while (!neighborhoods.empty() && improved)
    {
        improved = false;

        // Ordena vizinhanças pelo desempenho (menos falhas na busca anterior)
        sort(neighborhoods.begin(), neighborhoods.end(), [](auto &a, auto &b)
             { return a.second < b.second; });

        for (size_t i = 0; i < neighborhoods.size(); ++i)
        {
            auto &neighborhood = neighborhoods[i].first;

            if (neighborhood(aircrafts, solution))
            {
                // Reinicia a contagem de falhas e reinicia a busca
                neighborhoods[i].second = 0;
                improved = true;
                break;
            }
            else
            {
                // Incrementa a contagem de falhas
                neighborhoods[i].second++;
            }
        }

        // Remove vizinhanças com desempenho ruim por várias iterações
        neighborhoods.erase(
            remove_if(neighborhoods.begin(), neighborhoods.end(), [](auto &n)
                      { return n.second > 3; }),
            neighborhoods.end());
    }
}

void applyShiftLocalSearch(vector<Aircraft> aircrafts, Solution &solution)
{
    bool improved = true;

    while (improved)
    {
        improved = false;
        for (size_t i = 0; i < solution.aircraft_sequence.size(); ++i)
        {
            auto aircraft = solution.aircraft_sequence[i];

            for (size_t j = 0; j < solution.aircraft_sequence.size(); ++j)
            {
                if (i != j)
                {
                    // Remove a aeronave da posição original
                    solution.aircraft_sequence.erase(solution.aircraft_sequence.begin() + i);

                    // Insere na nova posição
                    solution.aircraft_sequence.insert(solution.aircraft_sequence.begin() + j, aircraft);

                    if (viability_verifier(aircrafts, solution))
                    {
                        double new_obj = calculateObjectiveFunction(aircrafts, solution);
                        if (new_obj < solution.objective_function)
                        {
                            solution.objective_function = new_obj;
                            improved = true;
                            break;
                        }
                    }

                    // Reverte caso a solução não seja viável
                    solution.aircraft_sequence.erase(solution.aircraft_sequence.begin() + j);
                    solution.aircraft_sequence.insert(solution.aircraft_sequence.begin() + i, aircraft);
                }
            }
            if (improved)
                break;
        }
    }
}

Solution runILSWithRVND(vector<Aircraft> aircrafts, Solution initial_solution, int max_iterations, int max_ils_iterations)
{
    Solution best_solution = initial_solution;
    Solution current_solution = initial_solution;
    double best_cost = initial_solution.objective_function;

    for (int i = 0; i < max_iterations; ++i)
    {
        int ils_iterations = 0;

        while (ils_iterations <= max_ils_iterations)
        {
            // Aplica RVND para intensificação
            applyLocalSearch(aircrafts, current_solution);
            updateObjectiveFunction(aircrafts, current_solution);

            // Aceita a solução se for melhor e reinicia as iterações do ILS
            if (current_solution.objective_function < best_cost)
            {
                best_solution = current_solution;
                best_cost = current_solution.objective_function;
                ils_iterations = 0;
            }
            else
                ils_iterations++;

            // Aplica uma perturbação para explorar novas regiões
            applyPerturbation(aircrafts, current_solution);
            updateObjectiveFunction(aircrafts, current_solution);
        }
    }

    return best_solution;
}

// Aplica perturbação trocando elementos aleatoriamente na sequência
void applyPerturbation(vector<Aircraft> &aircrafts, Solution &solution)
{
    srand(time(NULL));

    if (solution.aircraft_sequence.size() > 1)
    {
        for (int k = 0; k < 5; ++k) // Número de trocas aleatórias
        {

            int idx2 = rand() % solution.aircraft_sequence.size();
            int idx1 = rand() % solution.aircraft_sequence.size();

            if(idx1 == idx2)
            {
                k--;
                continue;
            }
                
            swap(solution.aircraft_sequence[idx1], solution.aircraft_sequence[idx2]);
        }

        // Ajusta os tempos de pouso e atualiza a função objetivo
        for (size_t i = 0; i < solution.aircraft_sequence.size(); ++i)
        {
            int current_aircraft_id = solution.aircraft_sequence[i].first;
            int previous_time = (i > 0) ? solution.aircraft_sequence[i - 1].second : 0;
            int separation_time = (i > 0) ? aircrafts[current_aircraft_id].separation_times[solution.aircraft_sequence[i - 1].first] : 0;

            int scheduled_time = max(solution.aircraft_sequence[i].second, previous_time + separation_time);
            scheduled_time = max(scheduled_time, aircrafts[current_aircraft_id].earliest_time);
            scheduled_time = min(scheduled_time, aircrafts[current_aircraft_id].latest_time);

            solution.aircraft_sequence[i].second = scheduled_time;
        }

        updateObjectiveFunction(aircrafts, solution);
    }
}

bool shiftNeighborhood(vector<Aircraft> &aircrafts, Solution &solution)
{
    for (size_t i = 0; i < solution.aircraft_sequence.size(); ++i)
    {
        auto aircraft = solution.aircraft_sequence[i];

        for (size_t j = 0; j < solution.aircraft_sequence.size(); ++j)
        {
            if (i != j)
            {
                // Remove a aeronave da posição original
                solution.aircraft_sequence.erase(solution.aircraft_sequence.begin() + i);

                // Insere na nova posição
                solution.aircraft_sequence.insert(solution.aircraft_sequence.begin() + j, aircraft);

                if (viability_verifier(aircrafts, solution))
                {
                    double new_obj = calculateObjectiveFunction(aircrafts, solution);
                    if (new_obj < solution.objective_function)
                    {
                        solution.objective_function = new_obj;
                        cout << "Custo: " << solution.objective_function << endl;
                        return true;
                    }
                }

                // Reverte caso a solução não seja viável
                solution.aircraft_sequence.erase(solution.aircraft_sequence.begin() + j);
                solution.aircraft_sequence.insert(solution.aircraft_sequence.begin() + i, aircraft);
            }
        }
    }
    return false;
}

bool swapNeighborhood(vector<Aircraft> &aircrafts, Solution &solution)
{
    bool improved = false;

    for (size_t i = 0; i < solution.aircraft_sequence.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < solution.aircraft_sequence.size(); ++j)
        {
            swap(solution.aircraft_sequence[i], solution.aircraft_sequence[j]); // Realiza a troca

            if (viability_verifier(aircrafts, solution))
            {
                double new_obj = calculateObjectiveFunction(aircrafts, solution);
                if (new_obj < solution.objective_function)
                {
                    solution.objective_function = new_obj;
                    improved = true;
                    cout << "Custo: " << solution.objective_function << endl;
                }
            }

            swap(solution.aircraft_sequence[i], solution.aircraft_sequence[j]); // Reverte caso não seja viável
        }
    }

    return improved;
}

bool twoOptNeighborhood(vector<Aircraft> &aircrafts, Solution &solution)
{
    for (size_t i = 0; i < solution.aircraft_sequence.size() - 1; ++i)
    {
        for (size_t j = i + 1; j < solution.aircraft_sequence.size(); ++j)
        {
            reverse(solution.aircraft_sequence.begin() + i, solution.aircraft_sequence.begin() + j + 1); // Inverte o subvetor

            if (viability_verifier(aircrafts, solution))
            {
                updateObjectiveFunction(aircrafts, solution);
                cout << "Custo: " << solution.objective_function << endl;
                return true;
            }

            reverse(solution.aircraft_sequence.begin() + i, solution.aircraft_sequence.begin() + j + 1); // Reverte a inversão
        }
    }
    return false;
}

#include "../include/defines.hpp"
#include "../include/Aircraft_Struct.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/Solution_Struct.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Runway_Schedule.hpp"
#include "../include/Populational_Strategy.hpp"
#include "../include/Search_Strategy.hpp"

void populationalStrategy(vector<Aircraft> &aircrafts, Solution &solution, size_t population_size, size_t generations)
{
    auto start_time = chrono::high_resolution_clock::now(); 

    solution.heuristic = "ACO";
    ACO(aircrafts, solution, population_size, generations);

    auto end_time = chrono::high_resolution_clock::now();  
    chrono::duration<double> elapsed_time = end_time - start_time; 

    solution.execution_time = elapsed_time.count();
    printSolution(aircrafts, solution);
}

void ACO(vector<Aircraft> &aircrafts, Solution &solution, size_t num_ants, size_t iterations)
{
    size_t num_aircrafts = aircrafts.size();
    vector<vector<double>> pheromone;
    
    // Inicializa a matriz de feromônios com um valor base e ajuste heurístico
    initializePheromones(pheromone, num_aircrafts, solution.initial_pheromone, aircrafts);

    Solution best_solution = NULL;
    size_t best_objective;
    size_t stagnant_iterations = 0;
    size_t max_stagnant_iterations = 20;
    vector<Solution> ant_solutions(num_ants, Solution(solution.num_runways));

    for (size_t iter = 0; iter < iterations; iter++)
    {
        for (size_t ant = 0; ant < num_ants; ant++)
        {
            // Constrói uma solução com base nos feromônios e nas regras de separação
            constructSolution(aircrafts, pheromone, solution.num_runways, solution.exploration_rate, solution);
            ant_solutions[ant] = copySolution(solution);
            scheduleLandingTimes(aircrafts, ant_solutions[ant]);
            updateObjectiveFunction(aircrafts, ant_solutions[ant]);
            if(ant==0 && iter==0){
                best_solution = copySolution(ant_solutions[ant]);
                best_objective = ant_solutions[ant].objective_function;
            }
                
            
            // Atualiza a melhor solução encontrada até agora
            if (ant_solutions[ant].objective_function < best_objective)
            {
                best_solution = copySolution(ant_solutions[ant]);
                best_objective = ant_solutions[ant].objective_function;
                stagnant_iterations = 0;
            }
        }
        // Atualiza os níveis de feromônio com base nas melhores soluções encontradas
        updatePheromone(ant_solutions, pheromone, best_solution.evaporation_rate);

        // Critério de parada por estagnação
        stagnant_iterations++;
        if (stagnant_iterations >= max_stagnant_iterations)
            break;
    }
    solution.num_runways = best_solution.num_runways;
    solution.objective_function = best_solution.objective_function;
    for (size_t r = 0; r < solution.schedules.size(); r++)
    {
        Node *current = solution.schedules[r].getHead();
        while (current != nullptr)
        {
            Node *next = current->next;
            solution.schedules[r].remove(current);
            current = next;
        }
    }

    for (size_t r = 0; r < best_solution.schedules.size(); r++)
    {
        Node *current = best_solution.schedules[r].getHead();
        while (current != nullptr)
        {
            solution.schedules[r].push_back(current->aircraft, current->landing_time);
            current = current->next;
        }
    }
    solution = copySolution(best_solution);
    scheduleLandingTimes(aircrafts, solution);
    updateObjectiveFunction(aircrafts, solution);
}

void initializePheromones(vector<vector<double>> &pheromone, size_t num_aircrafts, double initial_pheromone, vector<Aircraft> &aircrafts)
{
    // Inicializa a matriz de feromônios com o valor base
    pheromone.resize(num_aircrafts, vector<double>(num_aircrafts, initial_pheromone));

    
    // Ajusta os feromônios considerando as penalizações das aeronaves
    for (size_t i = 0; i < num_aircrafts; i++)
        for (size_t j = 0; j < num_aircrafts; j++)
        {
            if (i == j)
                pheromone[i][j] = 0.0;
            else 
            {
                if(aircrafts[i].latest_time < aircrafts[j].earliest_time)
                {
                    pheromone[i][j] = 1.0;
                }
                else if(aircrafts[i].earliest_time > aircrafts[j].latest_time)
                {
                    pheromone[i][j] = 0.0;
                }
                else
                {
                    pheromone[i][j] = 0.5;
                }
            }
        }
}

void updatePheromone(vector<Solution> &solutions, vector<vector<double>> &pheromone, double evaporation_rate)
{
    // Evaporação global do feromônio para evitar acúmulo excessivo
    for (size_t i = 0; i < pheromone.size(); i++)
        for (size_t j = 0; j < pheromone[i].size(); j++)
            pheromone[i][j] *= (1 - evaporation_rate);

    // Atualiza os feromônios com base nas soluções encontradas
    for (size_t s = 0; s < solutions.size(); s++)
    {
        Solution &sol = solutions[s];
        double contribution = sol.pheromone_deposit / (sol.objective_function + 1e-6);

        // Atualiza os feromônios entre aeronaves adjacentes em cada pista
        for (size_t r = 0; r < sol.schedules.size(); r++)
        {
            Node *current = sol.schedules[r].getHead();
            while (current)
            {
                Node *another = current->next;
                while (another)
                {
                    int a1 = current->aircraft.plane_index;
                    int a2 = another->aircraft.plane_index;
                    pheromone[a1][a2] += contribution;
                    another = another->next;
                }
                current = current->next;
            }
        }
    }
}

size_t chooseAircraft(vector<double> &probabilities, vector<Aircraft> &aircrafts, double exploration_rate, vector<bool> &assigned)
{
    double sum_probabilities = 0.0;

    for(size_t i = 0; i < probabilities.size(); i++)
        if(!assigned[i])
            sum_probabilities += probabilities[i];

    double rand_value = ((double)rand() / RAND_MAX);

    // Exploração aleatória
    if (rand_value < exploration_rate)
        return rand() % probabilities.size();

    // Gera um valor aleatório para a escolha da aeronave
    rand_value *= sum_probabilities;
    double cumulative_prob = 0.0;

    // Percorre as probabilidades acumuladas e seleciona a aeronave correspondente
    for (size_t j = 0; j < probabilities.size(); j++)
    {
        if(assigned[j])
            continue;
        cumulative_prob += probabilities[j];
        if (cumulative_prob >= rand_value)
            return j;
    }

    // Retorna a última aeronave em caso de erro numérico
    return probabilities.size() - 1; 
}

bool isFeasibleInsertion(Runway_Schedule &runway, Aircraft &aircraft, Node *position)
{
    // Obtém a aeronave anterior na fila, caso exista
    Node *prev = position ? position->prev : runway.getTail();
    

    // Verifica se a aeronave pode ser inserida respeitando as regras de separação
    if (prev)
    {
        size_t min_separation = aircraft.separation_times[prev->aircraft.plane_index];

        if (aircraft.latest_time < prev->landing_time + min_separation)
            return false;
    }

    return true;
}

void constructSolution(vector<Aircraft> &aircrafts, vector<vector<double>> &pheromone, size_t num_runways, double exploration_rate, Solution &solution)
{
    solution.schedules.clear();
    solution.schedules.resize(num_runways);
    // Vetor de controle para marcar quais aeronaves já foram alocadas
    vector<bool> assigned(aircrafts.size(), false);

    // Itera sobre todas as aeronaves para decidir a ordem de pouso
    for (size_t i = 0; i < aircrafts.size(); i++)
    {
        // Vetor para armazenar as probabilidades de escolha
        vector<double> probabilities(aircrafts.size(), 0.0);

        for (size_t j = 0; j < aircrafts.size(); j++)
            if (!assigned[j])
                probabilities[j] += pheromone[i][j];

        // Escolhe uma aeronave com base nas probabilidades calculadas
        size_t selected_aircraft = chooseAircraft(probabilities, aircrafts, exploration_rate, assigned);
        assigned[selected_aircraft] = true;

        // Variáveis auxiliares para encontrar a melhor pista e posição de pouso
        size_t best_runway = 0;
        size_t best_objective = numeric_limits<size_t>::max();
        Node *best_position = nullptr;

        // Itera sobre todas as pistas disponíveis para encontrar a melhor opção para pouso
        for (size_t r = 0; r < num_runways; r++)
        {
            Runway_Schedule &runway = solution.schedules[r];

            // Percorre todas as posições possíveis dentro da pista atual
            for (size_t j = 0; j <= runway.getSize(); j++)
            {
                Node *current = runway.getHead();

                // Avança até a posição correta dentro da pista
                for (size_t k = 0; k < j && current; k++)
                    current = current->next;

                // Verifica se a aeronave pode ser inserida na posição atual
                if (!isFeasibleInsertion(runway, aircrafts[selected_aircraft], current))
                    continue;

                // Insere temporariamente a aeronave na pista para avaliar a função objetivo
                runway.insert(current, aircrafts[selected_aircraft], aircrafts[selected_aircraft].target_time);
                
                updateObjectiveFunction(aircrafts, solution);

                // Se a nova solução é melhor que a melhor encontrada até agora, atualiza os valores
                if (solution.objective_function < best_objective)
                {
                    best_objective = solution.objective_function;
                    best_runway = r;
                    best_position = current;
                }

                // Remove a inserção temporária para testar outras posições
                if (current!=nullptr)
                    runway.remove(current->prev);
                else
                    runway.remove(runway.getTail());
            }
        }
        // Insere a aeronave na melhor posição e pista encontrada
        solution.schedules[best_runway].insert(best_position, aircrafts[selected_aircraft], aircrafts[selected_aircraft].target_time);
    }
}
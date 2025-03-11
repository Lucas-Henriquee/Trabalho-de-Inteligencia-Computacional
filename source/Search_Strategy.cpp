#include "../include/Search_Strategy.hpp"
#include "../include/Solution_Functions.hpp"
#include "../include/Aircraft_Functions.hpp"
#include "../include/defines.hpp"

void constructiveStrategy(vector<Aircraft> &aircrafts, Solution &solution)
{
    NEHConstructive(aircrafts, solution, aircrafts);
    printSolution(solution);
}

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
    viability_verifier(aircrafts, solution);
    Solution best_solution = copySolution(solution);
    bool improved = false;
    size_t non_improving = 0;
    do
    {
        VND(aircrafts, solution, best_solution);
        if (solution.objective_function < best_solution.objective_function)
        {
            best_solution = copySolution(solution);
            improved = true;
            non_improving = 0;
        }
        destroyed_aircrafts = destroySolution(solution);
        NEHConstructive(destroyed_aircrafts, solution, destroyed_aircrafts);
        if (improved)
        {
            improved = false;
            non_improving++;
        }
    } while (non_improving < 100);
}

void NEHConstructive(vector<Aircraft> &aircrafts, Solution &solution, vector<Aircraft> &destroyed_aircrafts)
{
    if (destroyed_aircrafts.empty() || solution.schedules.empty())
        return;

    // TODO: Iterar sobre as aeronaves para encontrar a melhor posição em qualquer pista
    for (size_t i = 0; i < destroyed_aircrafts.size(); i++)
    {
        Aircraft aircraft_to_insert = destroyed_aircrafts[i];
        Node *best_position = nullptr;
        size_t best_runway = 0;
        size_t best_objective = static_cast<size_t>(-1);

        for (size_t r = 0; r < solution.schedules.size(); r++)
        {
            Runway_Schedule &runway = solution.schedules[r];

            for (size_t j = 0; j <= runway.getSize(); j++) // Inserção em todas as posições possíveis
            {
                Node *current = runway.getHead();

                for (size_t k = 0; k < j && current; k++)
                    current = current->next;

                runway.insert(current, aircraft_to_insert, aircraft_to_insert.target_time);
                updateObjectiveFunction(aircrafts, solution);

                if (solution.objective_function < best_objective)
                {
                    best_objective = solution.objective_function;
                    best_position = current;
                    best_runway = r;
                }

                if (current!=nullptr)
                    runway.remove(current->prev);
                else
                    runway.remove(runway.getTail());
            }
        }

        // TODO: Inserir o avião na melhor posição encontrada
        solution.schedules[best_runway].insert(best_position, aircraft_to_insert, aircraft_to_insert.target_time);
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
    // TODO: Inicializar o vetor de aeronaves destruídas
    vector<Aircraft> destroyed_aircrafts;

    if (solution.schedules.empty())
        return destroyed_aircrafts;

    // TODO: Definir quantas aeronaves serão removidas aleatoriamente
    size_t num_destroyed_aircrafts = rand() % int(ceil(solution.schedules.size() * 3)); 

    for (size_t i = 0; i < num_destroyed_aircrafts; i++)
    {
        // TODO: Escolher uma pista aleatória para remover uma aeronave
        size_t random_runway = rand() % solution.schedules.size();

        if (solution.schedules[random_runway].getSize() == 0)
            continue;

        // TODO: Escolher uma aeronave aleatória dentro da pista selecionada
        int random = rand() % solution.schedules[random_runway].getSize();

        Node *current = solution.schedules[random_runway].getHead();

        for (size_t j = 0; j < random; j++)
            current = current->next;

        // TODO: Armazenar e remover a aeronave selecionada
        destroyed_aircrafts.push_back(current->aircraft);
        solution.schedules[random_runway].remove(current);
    }

    return destroyed_aircrafts;
}

vector<Aircraft> destroyRunway(Solution &solution)
{
    // TODO: Inicializar o vetor de aeronaves destruídas
    vector<Aircraft> destroyed_aircrafts;

    if (solution.schedules.size() < 2)
        return destroyed_aircrafts;

    // TODO: Escolher uma pista aleatória para remover todas as aeronaves
    size_t runway_to_destroy = rand() % solution.schedules.size();

    // TODO: Armazenar todas as aeronaves da pista antes de removê-las
    Node *current = solution.schedules[runway_to_destroy].getHead();

    while (current)
    {
        destroyed_aircrafts.push_back(current->aircraft);
        current = current->next;
    }

    // TODO: Remover todas as aeronaves da pista escolhida
    while (solution.schedules[runway_to_destroy].getHead())
        solution.schedules[runway_to_destroy].remove(solution.schedules[runway_to_destroy].getHead());

    return destroyed_aircrafts;
}

void VND(vector<Aircraft> &aircrafts, Solution &solution, Solution &best_solution)
{
    bool improved;

    do
    {
        improved = false;

        // TODO: Aplicar Swap (troca entre duas aeronaves na mesma pista)
        if (applySwap(aircrafts, solution, best_solution))
        {
            improved = true;
            continue;
        }

        // TODO: Aplicar Shift (mover uma aeronave e ajustar as demais)
        if (applyShift(aircrafts, solution, best_solution))
        {
            improved = true;
            continue;
        }

        // TODO: Aplicar Runway Swap (troca entre pistas diferentes)
        if (applyRunwaySwap(aircrafts, solution, best_solution))
            improved = true;

    } while (improved);
}

bool applySwap(vector<Aircraft> &aircrafts, Solution &solution, Solution &best_solution)
{
    for (size_t r = 0; r < solution.schedules.size(); r++) // Iterar sobre as pistas
    {
        // TODO: Obter o primeiro nó da pista atual
        Node *current = solution.schedules[r].getHead();

        while (current && current->next)
        {
            // TODO: Trocar as aeronaves de posição
            swap(current->aircraft, current->next->aircraft);
            updateObjectiveFunction(aircrafts, solution);

            // TODO: Verificar se a troca melhorou a solução
            if (solution.objective_function < best_solution.objective_function)
            {
                best_solution = copySolution(solution);
                return true;
            }

            // TODO: Se não melhorou, reverter a troca
            swap(current->aircraft, current->next->aircraft);
            current = current->next;
        }
    }
    return false;
}

bool applyShift(vector<Aircraft> &aircrafts, Solution &solution, Solution &best_solution)
{
    for (size_t r = 0; r < solution.schedules.size(); r++) // Iterar sobre as pistas
    {
        // TODO: Obter o primeiro nó da pista atual
        Node *current = solution.schedules[r].getHead();

        while (current)
        {
            // TODO: Remover temporariamente a aeronave
            Aircraft temp = current->aircraft;
            solution.schedules[r].remove(current);

            // TODO: Tentar inserir a aeronave em todas as posições possíveis
            Node *insertPos = solution.schedules[r].getHead();
            while (insertPos)
            {
                solution.schedules[r].insert(insertPos, temp, temp.target_time);
                updateObjectiveFunction(aircrafts, solution);

                // TODO: Verificar se a nova posição melhora a solução
                if (solution.objective_function < best_solution.objective_function)
                {
                    best_solution = copySolution(solution);
                    return true;
                }

                // TODO: Se não melhorar, remover e testar a próxima posição
                solution.schedules[r].remove(insertPos->prev);
                insertPos = insertPos->next;
            }

            // TODO: Se nenhuma posição foi melhor, inserir de volta na posição original
            solution.schedules[r].push_back(temp, temp.target_time);
            current = current->next;
        }
    }

    return false;
}

bool applyRunwaySwap(vector<Aircraft> &aircrafts, Solution &solution, Solution &best_solution)
{
    if (solution.schedules.size() < 2)
        return false; 

    // TODO: Iterar sobre todas as combinações de pistas
    for (size_t r1 = 0; r1 < solution.schedules.size(); r1++)
    {
        for (size_t r2 = r1 + 1; r2 < solution.schedules.size(); r2++)
        {
            // TODO: Percorrer aeronaves da primeira pista
            Node *node1 = solution.schedules[r1].getHead();
            while (node1)
            {
                // TODO: Percorrer aeronaves da segunda pista
                Node *node2 = solution.schedules[r2].getHead();

                while (node2)
                {
                    // TODO: Tentar trocar um avião entre as pistas r1 e r2
                    Aircraft a1 = node1->aircraft;
                    Aircraft a2 = node2->aircraft;

                    // TODO: Remover as aeronaves das pistas atuais
                    solution.schedules[r1].remove(node1);
                    solution.schedules[r2].remove(node2);

                    // TODO: Inserir as aeronaves nas pistas trocadas
                    solution.schedules[r1].push_back(a2, a2.target_time);
                    solution.schedules[r2].push_back(a1, a1.target_time);

                    // TODO: Atualizar a função objetivo
                    updateObjectiveFunction(aircrafts, solution);

                    // TODO: Se a solução melhorou, manter a troca
                    if (solution.objective_function < best_solution.objective_function)
                    {
                        best_solution = copySolution(solution);
                        return true;
                    }

                    // TODO: Se não melhorou, desfazer a troca
                    solution.schedules[r1].remove(solution.schedules[r1].getTail());
                    solution.schedules[r2].remove(solution.schedules[r2].getTail());

                    solution.schedules[r1].push_back(a1, a1.target_time);
                    solution.schedules[r2].push_back(a2, a2.target_time);

                    node2 = node2->next;
                }
                node1 = node1->next;
            }
        }
    }

    return false;
}
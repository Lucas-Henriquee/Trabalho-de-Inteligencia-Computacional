


/*
Pseudocodigo ils_rvnd
    Procedimento ILS-RVND(MaxIter, MaxIterILS, v)
	    CarregaDados();
	    f* ← ∞;
	    para i = 1, ..., MaxIterfaça
	        s ← GeraSoluçãoInicial(v, MaxIter, semente);
	        s' ← s;
	        iterILS ← 0;
	        enquanto iterILS ≤ MaxIterILSfaça
	            s ← RVND(s);
	            se f(s) <f(s') então
	                s' ← s;
	                iterILS← 0;
	            fim se
	            s' ← Perturbação(s', semente);
	            iterILS ← iterILS + 1;
	        fim enquanto
	            se f(s') <f*então
	                    s* ← s';
	                    f* ← f(s');
	            fim se
	    fim para
	    retorne s*;
	fimILS-RVND.
*/

/*
#include <defines.hpp>
#include <Solution_Functions.hpp>



// Estrutura para representar uma cidade com coordenadas (x, y)
struct City {
    int x, y;
};

// Função para calcular a distância entre duas cidades
double distance(const City& a, const City& b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Função para calcular o custo total de uma rota
double totalDistance(const vector<int>& route, const vector<City>& cities) {
    double total = 0.0;
    for (size_t i = 0; i < route.size() - 1; ++i) {
        total += distance(cities[route[i]], cities[route[i + 1]]);
    }
    total += distance(cities[route.back()], cities[route[0]]); // Volta para a cidade inicial
    return total;
}

// Função para gerar uma solução inicial aleatória
vector<int> generateInitialSolution(int n) {
    vector<int> solution(n);
    for (int i = 0; i < n; ++i) {
        solution[i] = i;
    }
    random_shuffle(solution.begin(), solution.end());
    return solution;
}

// Função para realizar uma perturbação na solução
vector<int> perturb(const vector<int>& solution) {
    vector<int> newSolution = solution;
    int n = newSolution.size();
    int i = rand() % n;
    int j = rand() % n;
    swap(newSolution[i], newSolution[j]);
    return newSolution;
}

// Função para realizar a busca local usando RVND
vector<int> rvnd(vector<int> solution, const vector<City>& cities) {
    vector<vector<int>> neighborhoods = {
        {1, 2}, // Exemplo de vizinhanças (swap, 2-opt)
        {2, 3}  // Outras vizinhanças podem ser adicionadas
    };

    bool improved = true;
    while (improved) {
        improved = false;
        for (const auto& neighborhood : neighborhoods) {
            for (int move : neighborhood) {
                vector<int> newSolution = solution;
                if (move == 1) { // Swap
                    int i = rand() % solution.size();
                    int j = rand() % solution.size();
                    swap(newSolution[i], newSolution[j]);
                } else if (move == 2) { // 2-opt
                    int i = rand() % solution.size();
                    int j = rand() % solution.size();
                    if (i > j) swap(i, j);
                    reverse(newSolution.begin() + i, newSolution.begin() + j);
                }

                double currentCost = totalDistance(solution, cities);
                double newCost = totalDistance(newSolution, cities);
                if (newCost < currentCost) {
                    solution = newSolution;
                    improved = true;
                }
            }
        }
    }
    return solution;
}

// Função principal do ILS-RVND

fiz algumas mudanças já

vector<int> ilsRvnd(const vector<Aircraft>& aircrafts, int maxIterations) 
{
	Solution best_solution;
    constructInitialSolution(aircrafts, best_solution);
    calculateObjectiveFunction(aircrafts, best_solution);
	double best_cost = best_solution.objective_function;

    for (size_t i = 0; i < maxIterations; ++i) 
	{
        Solution current_solution = perturb(best_solution);
        current_solution = rvnd(current_solution, cities);
        double current_cost = calculateObjectiveFunction(current_solution, cities);

        if (current_cost < best_cost) 
		{
            best_solution = current_solution;
            best_cost = currentCost;
        }
    }

    return best_solution;
}
*/
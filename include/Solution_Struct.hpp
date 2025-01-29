#ifndef SOLUTION_STRUCT_HPP
#define SOLUTION_STRUCT_HPP

#include "defines.hpp"
#include "Aircraft_Struct.hpp"

struct Solution
{
    // Vetor de pares (indice da aeronave, tempo de pouso)
    vector<pair<Aircraft, int>> aircraft_sequence;
    size_t objective_function = 0;
};

#endif // SOLUTION_STRUCT_HPP
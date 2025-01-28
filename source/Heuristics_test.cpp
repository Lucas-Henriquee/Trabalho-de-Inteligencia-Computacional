// Procedimento ILS-RVND(MaxIter, MaxIterILS, aircrafts)
//     s* ← ∞ // Melhor solução global
//     f* ← ∞ // Melhor custo global
//     para i = 1, ..., MaxIter faça
//         s ← GeraSoluçãoInicial(aircrafts) // Solução inicial com heurística construtiva
//         f(s) ← calculaCusto(s, aircrafts)
//         iterILS ← 0
//         enquanto iterILS ≤ MaxIterILS faça
//             s ← RVND(s, aircrafts) // Refinamento com RVND
//             se f(s) < f* então
//                 s* ← s // Atualiza melhor solução
//                 f* ← f(s)
//                 iterILS ← 0
//             fim se
//             s ← Perturbação(s, aircrafts) // Perturba solução
//             iterILS ← iterILS + 1
//         fim enquanto
//     fim para
//     retorne s*
// fim procedimento

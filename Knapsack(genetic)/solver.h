#ifndef SOLVER_H
#define SOLVER_H
#include "parser.h"
#include <algorithm>
#include <vector>

class Solver {
    int N;                 
    long long K;           
    Item* items;          
    std::vector<int> best_solution; 
    long long best_fitness;       

public:
    Solver(): N(0), K(0), items(NULL), best_fitness(0) {};
    void SetData(int Size, long long capacity, Item* items_data);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    std::vector<int> GetSolution() {return best_solution;};
    long long GetTotalValue() {return best_fitness;};
    long long GetTotalWeight();
};
#endif

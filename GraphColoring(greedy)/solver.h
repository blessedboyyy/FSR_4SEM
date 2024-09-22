#ifndef SOLVER_H
#define SOLVER_H
#include "parser.h"
#include <vector>

class Solver {
    int N; 
    std::vector<std::pair<int, int>> edges; 
    std::vector<std::vector<int>> adj; 
    std::vector<int> best_solution; 
    int total_colors; 

public:
    Solver(): N(0), edges(), adj(), best_solution(), total_colors(0) {};
    void SetData(int Size, std::vector<std::pair<int, int>> edges_data);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    std::vector<int> GetSolution() {return best_solution;};
    int GetTotalColors() {return total_colors;};
};
#endif

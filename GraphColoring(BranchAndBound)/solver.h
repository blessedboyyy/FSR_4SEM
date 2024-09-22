#ifndef SOLVER_H
#define SOLVER_H
#include "parser.h"
#include <vector>
#include <algorithm>
#include <cstdint>

struct State {
    std::vector<int> color; 
    int vertex;            
    int color_count;        
    int bound;
    State(int N): color(N, 0), vertex(0), color_count(0), bound(0) {}
};

class Solver {
    int N; 
    int E;
    std::vector<std::pair<int, int>> edges; 
    std::vector<std::vector<int>> adj; 
    std::vector<int> best_solution; 
    int best_color_count; 

public:
    Solver(): N(0), E(0), edges(), adj(), best_solution(), best_color_count(INT32_MAX) {};
    void SetData(int Size, std::vector<std::pair<int, int>> edges_data);
    void Clear();
    ~Solver() {Clear();};
    void Solve();
    std::vector<int> GetSolution() {return best_solution;};
    int GetTotalColors() {return best_color_count;};
private:
    int calculate_bound(const State& state);
};
#endif

#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>

void Solver::SetData(int Size, long long capacity, Item* items_data) {
    this->Clear();
    N = Size;
    K = capacity;
    items = items_data;
}

void Solver::Clear() {
    N = 0;
    K = 0;
    items = NULL;
    best_solution.clear();
    best_fitness = 0;
}

long long Solver::GetTotalWeight() {
    if(best_solution.empty()) return 0;
    long long total_weight = 0;
    for(int i = 0; i < N; ++i){
        if(best_solution[i]){
            total_weight += items[i].weight;
        }
    }
    return total_weight;
}

void Solver::Solve() {
    std::vector<long long> dp(K + 1, 0);

    std::vector<std::vector<int>> keep(N, std::vector<int>(K + 1, 0));

    for(int i = 0; i < N; ++i){
        for(long long w = K; w >= items[i].weight; --w){
            if(dp[w - items[i].weight] + items[i].value > dp[w]){
                dp[w] = dp[w - items[i].weight] + items[i].value;
                keep[i][w] = 1;
            }
        }
    }

    best_fitness = 0;
    long long best_weight = 0;
    for(long long w = 0; w <= K; ++w){
        if(dp[w] > best_fitness){
            best_fitness = dp[w];
            best_weight = w;
        }
    }

    best_solution = std::vector<int>(N, 0);
    long long w = best_weight;
    for(int i = N - 1; i >= 0; --i){
        if(keep[i][w] == 1){
            best_solution[i] = 1;
            w -= items[i].weight;
        }
    }
}

#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct ItemRatio {
    int index;                  
    double ratio;              
};

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
    std::vector<ItemRatio> item_ratios(N);
    for(int i = 0; i < N; ++i){
        item_ratios[i].index = i;
        if(items[i].weight == 0){
            item_ratios[i].ratio = (double)items[i].value; 
        }
        else{
            item_ratios[i].ratio = (double)items[i].value / items[i].weight;
        }
    }

    std::sort(item_ratios.begin(), item_ratios.end(),
              [](const ItemRatio &a, const ItemRatio &b) -> bool {
                  return a.ratio > b.ratio;
              });

    long long current_weight = 0;
    long long current_value = 0;
    best_solution = std::vector<int>(N, 0); 

    for(auto &item : item_ratios){
        if(current_weight + items[item.index].weight <= K){
            best_solution[item.index] = 1; 
            current_weight += items[item.index].weight;
            current_value += items[item.index].value;
        }
    }

    best_fitness = current_value; 
}

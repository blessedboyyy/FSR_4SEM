#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>

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

double bound(const Node& node, int N, long long K, Item* items_sorted) {
    if(node.weight >= K)
        return 0;
    double profit_bound = node.profit;

    int j = node.level + 1;
    double totweight = node.weight;

    while(j < N && totweight + items_sorted[j].weight <= K){
        totweight += items_sorted[j].weight;
        profit_bound += items_sorted[j].value;
        j++;
    }

    if(j < N){
        profit_bound += (K - totweight) * ((double)items_sorted[j].value / items_sorted[j].weight);
    }

    return profit_bound;
}

void Solver::Solve() {
    std::vector<Item> items_sorted(N);
    for(int i = 0; i < N; i++) {
        items_sorted[i].value = items[i].value;
        items_sorted[i].weight = items[i].weight;
    }

    std::sort(items_sorted.begin(), items_sorted.end(), [](const Item& a, const Item& b) -> bool {
        double ratio_a = (double)a.value / a.weight;
        double ratio_b = (double)b.value / b.weight;
        return ratio_a > ratio_b;
    });

    auto cmp = [](const Node& a, const Node& b) -> bool {
        return a.bound < b.bound; 
    };
    std::priority_queue<Node, std::vector<Node>, decltype(cmp)> Q(cmp);
    std::vector<int> initial_selection(N, 0);
    Node root(-1, 0, 0, 0.0, initial_selection);
    root.bound = bound(root, N, K, items_sorted.data());
    Q.push(root);
    best_fitness = 0;
    best_solution = std::vector<int>(N, 0);

    while(!Q.empty()) {
        Node node = Q.top();
        Q.pop();
        if(node.bound <= best_fitness)
            continue;
        int level = node.level + 1;

        if(level >= N)
            continue;

        long long new_weight = node.weight + items_sorted[level].weight;
        long long new_profit = node.profit + items_sorted[level].value;
        if(new_weight <= K && new_profit > best_fitness) {
            best_fitness = new_profit;
            best_solution = node.items_selected;
            best_solution[level] = 1;
        }

        if(new_weight <= K) {
            std::vector<int> included_selection = node.items_selected;
            included_selection[level] = 1;
            Node included_node(level, new_profit, new_weight, 0.0, included_selection);
            included_node.bound = bound(included_node, N, K, items_sorted.data());
            if(included_node.bound > best_fitness)
                Q.push(included_node);
        }

        std::vector<int> excluded_selection = node.items_selected;
        excluded_selection[level] = 0;
        Node excluded_node(level, node.profit, node.weight, 0.0, excluded_selection);
        excluded_node.bound = bound(excluded_node, N, K, items_sorted.data());
        if(excluded_node.bound > best_fitness)
            Q.push(excluded_node);
    }

    std::vector<int> sorted_to_original(N, -1);
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            if(sorted_to_original[j] == -1 && items_sorted[i].value == items[j].value && items_sorted[i].weight == items[j].weight){
                sorted_to_original[i] = j;
                break;
            }
        }
    }

    std::vector<int> final_solution(N, 0);
    for(int i = 0; i < N; i++) {
        if(best_solution[i] == 1 && sorted_to_original[i] != -1){
            final_solution[sorted_to_original[i]] = 1;
        }
    }
    best_solution = final_solution;
}

#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void Solver::SetData(int Size, std::vector<std::pair<int, int>> edges_data){
    this->Clear();
    N = Size;
    edges = edges_data;
    adj.resize(N, std::vector<int>()); 
    for(auto &edge : edges){
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
}

void Solver::Clear(){
    N = 0;
    edges.clear();
    adj.clear();
    best_solution.clear();
    total_colors = 0;
}

void Solver::Solve(){
    best_solution = std::vector<int>(N, 0); 
    std::vector<int> vertex_order(N);
    for(int i = 0; i < N; ++i){
        vertex_order[i] = i;
    }

    std::sort(vertex_order.begin(), vertex_order.end(),
              [&](const int a, const int b) -> bool {
                  return adj[a].size() > adj[b].size();
              });

    int max_color = 0;
    for(auto vertex : vertex_order){
        std::set<int> used_colors;
        for(auto &neighbor : adj[vertex]){
            if(best_solution[neighbor] != 0){
                used_colors.insert(best_solution[neighbor]);
            }
        }

        int color = 1;
        while(used_colors.find(color) != used_colors.end()){
            color++;
        }

        best_solution[vertex] = color;
        if(color > max_color){
            max_color = color;
        }
    }

    total_colors = max_color;
}

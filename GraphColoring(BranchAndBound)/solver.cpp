#include "solver.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <climits>
#include <set>

void Solver::SetData(int Size, std::vector<std::pair<int, int>> edges_data){
    this->Clear();
    N = Size;
    E = edges_data.size();
    edges = edges_data;
    adj.resize(N, std::vector<int>()); 
    for(auto &edge : edges){
        adj[edge.first].push_back(edge.second);
        adj[edge.second].push_back(edge.first);
    }
}

void Solver::Clear(){
    N = 0;
    E = 0;
    edges.clear();
    adj.clear();
    best_solution.clear();
    best_color_count = INT32_MAX;
}

int Solver::calculate_bound(const State& state){
    int bound = state.color_count;
    std::vector<int> temp_color = state.color;
    std::vector<int> remaining_vertices;
    for(int v = state.vertex; v < N; v++){
        remaining_vertices.push_back(v);
    }
    std::sort(remaining_vertices.begin(), remaining_vertices.end(),
              [&](const int a, const int b) -> bool {
                  return adj[a].size() > adj[b].size();
              });
    for(auto v : remaining_vertices){
        std::set<int> used_colors;
        for(auto &neighbor : adj[v]){
            if(temp_color[neighbor] != 0){
                used_colors.insert(temp_color[neighbor]);
            }
        }
        int color = 1;
        while(used_colors.find(color) != used_colors.end()){
            color++;
        }
        if(color > bound){
            bound = color;
        }
        temp_color[v] = color;
    }
    return bound;
}

void Solver::Solve(){
    State initial(N);
    auto cmp = [&](const State& a, const State& b) -> bool {
        return a.bound > b.bound; 
    };
    std::priority_queue<State, std::vector<State>, decltype(cmp)> pq(cmp);
    initial.bound = calculate_bound(initial);
    pq.push(initial);
    
    while(!pq.empty()){
        State current = pq.top();
        pq.pop();
        if(current.bound >= best_color_count){
            continue;
        }
        if(current.vertex == N){
            if(current.color_count < best_color_count){
                best_color_count = current.color_count;
                best_solution = current.color;
            }
            continue;
        }
        for(int c = 1; c <= current.color_count + 1; c++){ 
            bool can_use = true;
            for(auto &neighbor : adj[current.vertex]){
                if(current.color[neighbor] == c){
                    can_use = false;
                    break;
                }
            }
            if(can_use){
                State child = current;
                child.color[current.vertex] = c;
                if(c > child.color_count){
                    child.color_count = c;
                }
                child.vertex += 1;
                child.bound = calculate_bound(child);
                if(child.bound < best_color_count){
                    pq.push(child);
                }
            }
        }
    }

    if(best_color_count != INT32_MAX){
    } else {
        best_color_count = N;
        best_solution = std::vector<int>(N, 1);
        for(int i = 0; i < N; i++) {
            best_solution[i] = i + 1;
        }
    }
}

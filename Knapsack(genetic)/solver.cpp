#include "solver.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

// Genetic algh parametrs
const int POPULATION_SIZE = 200;   
const int GENERATIONS = 1000;      
const double MUTATION_RATE = 0.02;  
const int TOURNAMENT_SIZE = 5;      
const int ELITE_COUNT = 5;        

int random_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

long long fitness(const std::vector<int>& chromosome, Item* items, int N, long long K) {
    long long total_value = 0;
    long long total_weight = 0;
    for(int i = 0; i < N; ++i){
        if(chromosome[i]){
            total_value += items[i].value;
            total_weight += items[i].weight;
        }
    }
    if(total_weight > K){
        long long penalty = 1000 * (total_weight - K); 
        return total_value - penalty;
    }
    return total_value;
}

std::vector<int> tournament_selection(const std::vector<std::vector<int>>& population, Item* items, int N, long long K) {
    int best = -1;
    long long best_fitness_val = -1;
    for(int i = 0; i < TOURNAMENT_SIZE; ++i){
        int idx = random_int(0, population.size()-1);
        long long fit = fitness(population[idx], items, N, K);
        if(fit > best_fitness_val){
            best_fitness_val = fit;
            best = idx;
        }
    }
    return population[best];
}

std::pair<std::vector<int>, std::vector<int>> crossover(const std::vector<int>& parent1, const std::vector<int>& parent2) {
    int n = parent1.size();
    std::vector<int> child1(n);
    std::vector<int> child2(n);
    for(int i = 0; i < n; ++i){
        if(rand() / double(RAND_MAX) < 0.5){
            child1[i] = parent1[i];
            child2[i] = parent2[i];
        }
        else{
            child1[i] = parent2[i];
            child2[i] = parent1[i];
        }
    }
    return {child1, child2};
}

void mutate(std::vector<int>& chromosome) {
    for(auto &gene : chromosome){
        if((rand() / double(RAND_MAX)) < MUTATION_RATE){
            gene = 1 - gene; 
        }
    }
}

std::vector<std::vector<int>> initialize_population(int population_size, int N, Item* items, long long K) {
    std::vector<std::vector<int>> population;
    population.reserve(population_size);
    for(int i = 0; i < N && population.size() < population_size; i++) {
        if(items[i].weight <= K){
            std::vector<int> chromosome(N, 0);
            chromosome[i] = 1;
            population.push_back(chromosome);
        }
    }
    while(population.size() < population_size){
        std::vector<int> chromosome(N, 0);
        long long total_weight = 0;
        for(int i = 0; i < N; i++){
            if(rand() / double(RAND_MAX) < 0.1){ 
                if(total_weight + items[i].weight <= K){
                    chromosome[i] = 1;
                    total_weight += items[i].weight;
                }
            }
        }
        population.push_back(chromosome);
    }

    return population;
}

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
    srand(time(0));
    std::vector<std::vector<int>> population = initialize_population(POPULATION_SIZE, N, items, K);
    // std::cout << "Initial Population (first 5 chromosomes):\n";
    // for(int i = 0; i < std::min(5, POPULATION_SIZE); i++) {
    //     for(int j = 0; j < N; j++) {
    //         std::cout << population[i][j] << " ";
    //     }
    //     std::cout << "\n";
    // }
    best_solution.clear();
    best_fitness = 0;
    for(int gen = 0; gen < GENERATIONS; ++gen){
        std::vector<std::pair<long long, std::vector<int>>> fitness_population;
        fitness_population.reserve(POPULATION_SIZE);
        for(auto &chromosome : population){
            long long fit = fitness(chromosome, items, N, K);
            fitness_population.emplace_back(fit, chromosome);
            if(fit > best_fitness){
                best_fitness = fit;
                best_solution = chromosome;
            }
        }
        std::sort(fitness_population.begin(), fitness_population.end(),
                  [](const std::pair<long long, std::vector<int>> &a, const std::pair<long long, std::vector<int>> &b) -> bool {
                      return a.first > b.first;
                  });
        std::vector<std::vector<int>> new_population;
        new_population.reserve(POPULATION_SIZE);
        for(int i = 0; i < ELITE_COUNT && i < fitness_population.size(); ++i){
            new_population.push_back(fitness_population[i].second);
        }
        while(new_population.size() < POPULATION_SIZE){
            std::vector<int> parent1 = tournament_selection(population, items, N, K);
            std::vector<int> parent2 = tournament_selection(population, items, N, K);
            std::pair<std::vector<int>, std::vector<int>> offspring = crossover(parent1, parent2);
            mutate(offspring.first);
            mutate(offspring.second);
            long long weight1 = 0;
            for(int i = 0; i < N; i++) {
                if(offspring.first[i]){
                    weight1 += items[i].weight;
                }
            }
            if(weight1 <= K){
                new_population.push_back(offspring.first);
            }

            if(new_population.size() < POPULATION_SIZE){
                long long weight2 = 0;
                for(int i = 0; i < N; i++) {
                    if(offspring.second[i]){
                        weight2 += items[i].weight;
                    }
                }
                if(weight2 <= K){
                    new_population.push_back(offspring.second);
                }
            }
        }
        population = new_population;
        // if(gen % 100 == 0){
        //     std::cout << "Generation " << gen << ": Best Fitness = " << best_fitness << "\n";
        // }
    }
    // std::cout << "Final Best Fitness = " << best_fitness << "\n";
}

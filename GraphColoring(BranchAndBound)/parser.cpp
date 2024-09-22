#include "parser.h"

void Parser::Clear() {
    N = 0;
    E = 0;
    edges.clear();
}

void Parser::Parse(std::string filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error: Failed to open the file, make sure it is located in the same directory: " << filename << std::endl;
        exit(1);
    }
    f >> N >> E;
    if (N <= 0 || E < 0) {
        std::cerr << "Invalid input." << std::endl;
        Clear();
        exit(1);
    }

    int u, v;
    for(int i = 0; i < E; i++) {
        f >> u >> v;
        if(f.fail()){
            std::cerr << "Invalid input." << std::endl;
            Clear();
            exit(1);
        }
        if(u < 0 || u >= N || v < 0 || v >= N){
            std::cerr << "Invalid input." << std::endl;
            Clear();
            exit(1);
        }
        edges.emplace_back(u, v);
    }
    f.close();

    // std::cout << "Total vertices: " << N << ", Total edges: " << E << "\n";
    // if(edges.empty()){
    //     std::cout << "Граф не содержит рёбер.\n";
    // } else {
    //     std::cout << "Граф содержит рёбра.\n";
    // }
}

#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class Parser {
    int N; 
    int E; 
    std::vector<std::pair<int, int>> edges; 

public:
    Parser(): N(0), E(0), edges() {};
    void Clear();
    ~Parser() {Clear();};
    void Parse(std::string filename);
    std::vector<std::pair<int, int>> GetEdges() {return edges;};
    int GetQuantity() {return N;};
};
#endif

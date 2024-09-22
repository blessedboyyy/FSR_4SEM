#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
#include <string>

struct Item {
    long long value;   
    long long weight;  
};

class Parser {
    int N;        
    long long K;   
    Item *I;       

public:
    Parser(): N(0), K(0), I(NULL){};
    void Clear();
    ~Parser() {Clear();};
    void Parse(std::string filename);
    Item *GetItems() {return I;};
    int GetQuantity() {return N;};
    long long GetCapacity() {return K;};
};
#endif

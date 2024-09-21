#ifndef PARSER_H
#define PARSER_H
#include <fstream>
#include <iostream>
#include <cmath>
#include <windows.h>

struct Spot {
    int id;
    double X;
    double Y;
};


double calc_dist(Spot &A, Spot &B);


class Parser {
    int N;
    Spot *s;
    double **Dist_Array;
    public:
    Parser(): N(0), s(NULL){};
    void Clear();
    ~Parser() {Clear();};
    void Parse(std::string filename);
    Spot *GetSpots() {return s;};
    int GetQuantity() {return N;};
    void Fill_Dist();
    double** Get_Dist() {return Dist_Array;};



};


#endif

#ifndef SOLVER_H
#define SOLVER_H
#include "parser.h"
#include <algorithm>
#include <vector>

class Solver {
    int N;
    double** Dist_Array;
    int* Path;
    double PathLen;
    public:
    Solver(): N(0), Dist_Array(NULL), Path(NULL) {};
    Solver(int Size, double** distar): N(Size), Dist_Array(distar)
        {Path = new int[N+1];};
    void SetData(int Size, double** distar);
    void Clear();
    ~Solver() {Clear();};
    double totalDistance();
    void twoOptSwap();
    void Solve();
    int* GetPath() {return Path;};
};

#endif

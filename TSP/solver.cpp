#include "solver.h"

void Solver::SetData(int Size, double** distar) {
    this->Clear();
    N = Size;
    if (N <= 0)
        return;

    Dist_Array = distar;
    Path = new int[N+1];
}

void Solver::Clear() {
    N = 0;
    Dist_Array = NULL;

    if (Path != NULL)
        delete [] Path;
}

double Solver::totalDistance() {
    double total = 0;
    for (int i = 0; i < N; ++i) {
        total += Dist_Array[i][(i + 1) % N];
    }
    return total;
}

void Solver::Solve() {
    for(int i=0; i<N; i++)
        Path[i] = i;
    Path[N] = Path[0];
    bool improvement = true;

    while(improvement) {
        improvement = false;
        for(int i = 0; i < N - 1; i++) {
            for(int j = i + 2; j < N; j++) {
                if(i == 0 && j == N - 1)
                    continue;
                double old_dist = Dist_Array[Path[i]][Path[i + 1]] + Dist_Array[Path[j]][Path[j + 1]];
                double new_dist = Dist_Array[Path[i]][Path[j]] + Dist_Array[Path[i + 1]][Path[j + 1]];

                if(new_dist < old_dist - 1e-6) {
                    int p = i + 1;
                    int q = j;
                    while(p < q) {
                        std::swap(Path[p], Path[q]);
                        p++;
                        q--;
                    }
                    improvement = true;
                }
            }
        }
    }
}

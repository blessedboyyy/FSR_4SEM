#include "solver.h"
#include <iostream>
#include <cmath>
#include <limits>

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
        delete[] Path;
    Path = NULL;
}

double Solver::totalDistance() {
    double total = 0;
    for (int i = 0; i < N; ++i) {
        total += Dist_Array[Path[i]][Path[i + 1]];
    }
    return total;
}

double calc_distance(int a, int b, double** Dist_Array) {
    return Dist_Array[a][b];
}

void Solver::apply3OptMove(int i, int j, int k, int moveType) {
    switch(moveType) {
        case 1:
            std::reverse(Path + i + 1, Path + j + 1);
            break;
        case 2:
            std::reverse(Path + j + 1, Path + k + 1);
            break;
        case 3:
            std::reverse(Path + i + 1, Path + j + 1);
            std::reverse(Path + j + 1, Path + k + 1);
            break;
        default:
            break;
    }
}

bool Solver::perform3OptMove(int i, int j, int k) {
    double old_dist = calc_distance(Path[i], Path[i + 1], Dist_Array) +
                      calc_distance(Path[j], Path[j + 1], Dist_Array) +
                      calc_distance(Path[k], Path[k + 1], Dist_Array);

    double new_dist1 = calc_distance(Path[i], Path[j], Dist_Array) +
                       calc_distance(Path[i + 1], Path[j + 1], Dist_Array) +
                       calc_distance(Path[k], Path[k + 1], Dist_Array);

    if(new_dist1 < old_dist - 1e-6) {
        apply3OptMove(i, j, k, 1);
        return true;
    }

    double new_dist2 = calc_distance(Path[i], Path[i + 1], Dist_Array) +
                       calc_distance(Path[j], Path[k], Dist_Array) +
                       calc_distance(Path[j + 1], Path[k + 1], Dist_Array);

    if(new_dist2 < old_dist - 1e-6) {
        apply3OptMove(i, j, k, 2);
        return true;
    }

    double new_dist3 = calc_distance(Path[i], Path[j], Dist_Array) +
                       calc_distance(Path[i + 1], Path[k], Dist_Array) +
                       calc_distance(Path[j + 1], Path[k + 1], Dist_Array);

    if(new_dist3 < old_dist - 1e-6) {
        apply3OptMove(i, j, k, 3);
        return true;
    }


    return false;
}

void Solver::Solve() {
    for(int i = 0; i < N; i++)
        Path[i] = i;
    Path[N] = Path[0];

    bool improvement = true;

    while(improvement) {
        improvement = false;
        for(int i = 0; i < N - 2; i++) {
            for(int j = i + 2; j < N; j++) {
                for(int k = j + 2; k < N; k++) {
                    if(k >= N)
                        continue;

                    if(i == 0 && k == N -1)
                        continue;

                    if(perform3OptMove(i, j, k)) {
                        improvement = true;
                        break;
                    }
                }
                if(improvement)
                    break;
            }
            if(improvement)
                break;
        }
    }
    Path[N] = Path[0];
    PathLen = totalDistance();
}

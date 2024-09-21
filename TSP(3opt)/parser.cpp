#include "parser.h"

double calc_dist(Spot &A, Spot &B) {
    double dx = A.X - B.X;
    double dy = A.Y - B.Y;
    return sqrt(dx * dx + dy * dy);
}

void Parser::Clear() {
    if (s != NULL) {
        delete[] s;
        s = NULL;
    }

    if (Dist_Array != NULL) {
        for(int i = 0; i < N; i++) {
            if (Dist_Array[i] != NULL)
                delete[] Dist_Array[i];
        }
        delete[] Dist_Array;
        Dist_Array = NULL;
    }

    N = 0;
}

void Parser::Parse(std::string filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error: Could not open file, make sure that the file is located in the same directory " << filename << std::endl;
        return;
    }
    f >> N;
    std::cout << "N = " << N << std::endl;

    if (N <= 0) {
        std::cerr << "Invalid input" << std::endl;
        return;
    }

    s = new Spot[N];
    Dist_Array = new double*[N];
    for(int i = 0; i < N; i++)
        Dist_Array[i] = new double[N];

    for (int i = 0; i < N; i++) {
        f >> s[i].X >> s[i].Y;
        s[i].id = i;
    }
    f.close();
}

void Parser::Fill_Dist() {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            Dist_Array[i][j] = calc_dist(s[i], s[j]);
        }
    }
}

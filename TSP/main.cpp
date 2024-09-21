#include "parser.h"
#include "solver.h"
#include <iostream>
#include <cmath>
#include <string>
using namespace std;
#define ll long long
#define vi vector<int>
#define pi pair<int, int>
#define pb push_back
#define mp make_pair
#define fi first

int main(void) {
    Parser MyParser;
    Solver MySolver;

    std::string filename;
    //Input filename
    cout << "type in your filename: ";
    cin >> filename;

    MyParser.Parse(filename);
    int N = MyParser.GetQuantity();
    MyParser.Fill_Dist();
    double** Distances = MyParser.Get_Dist();
    MySolver.SetData(N, Distances);
    MySolver.Solve();
    int* final_path = MySolver.GetPath();
    cout << MySolver.totalDistance() << " " << final_path[0] << endl;
    for (int i = 0; i < N; i++) {
        cout << final_path[i] << " ";
    }
    cout << endl;



    return 0;
}


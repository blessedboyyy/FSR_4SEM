#include "parser.h"
#include "solver.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
    Parser MyParser;
    Solver MySolver;

    string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    MyParser.Parse(filename);
    int N = MyParser.GetQuantity();
    vector<pair<int, int>> edges = MyParser.GetEdges();

    // cout << "Parsed Data:\n";
    // cout << "Number of vertices = " << N << "\n";
    // cout << "Number of edges = " << edges.size() << "\n";
    // for(int i = 0; i < min((int)edges.size(), 10); i++) { 
    //     cout << "Edge " << i << ": " << edges[i].first << " - " << edges[i].second << "\n";
    // }

    MySolver.SetData(N, edges);
    MySolver.Solve();
    vector<int> best_solution = MySolver.GetSolution();
    int total_colors = MySolver.GetTotalColors();

    cout << total_colors << "\n";
    for(int i = 0; i < N; i++) {
        cout << best_solution[i] << " ";
    }
    cout << "\n";

    return 0;
}

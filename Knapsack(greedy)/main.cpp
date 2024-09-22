#include "parser.h"
#include "solver.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(void) {
    Parser MyParser;
    Solver MySolver;

    std::string filename;
    cout << "Enter the filename: ";
    cin >> filename;

    MyParser.Parse(filename);
    int N = MyParser.GetQuantity();
    long long K = MyParser.GetCapacity();
    Item* items = MyParser.GetItems();

    // cout << "Parsed Data:\n";
    // cout << "N = " << N << ", K = " << K << "\n";
    // for(int i = 0; i < min(N, 10); i++) { 
    //     cout << "Item " << i << ": Value = " << items[i].value << ", Weight = " << items[i].weight << "\n";
    // }

    MySolver.SetData(N, K, items);
    MySolver.Solve();
    vector<int> best_solution = MySolver.GetSolution();
    long long total_value = MySolver.GetTotalValue();

    cout << total_value << " " << best_solution[0] << "\n";
    for(int i = 0; i < N; i++) {
        cout << best_solution[i] << " ";
    }
    cout << "\n";

    return 0;
}

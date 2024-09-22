#include "parser.h"

void Parser::Clear() {
    if (I != NULL) {
        delete[] I;
        I = NULL;
    }
    N = 0;
    K = 0;
}

void Parser::Parse(std::string filename) {
    std::ifstream f(filename);
    if (!f.is_open()) {
        std::cerr << "Error: Failed to open the file, make sure it is located in the same directory: " << filename << std::endl;
        exit(1);
    }
    f >> N >> K;

    if (N <= 0 || K <= 0) {
        std::cerr << "Invalid input." << std::endl;
        exit(1);
    }

    I = new Item[N];
    long long sum_weights = 0;
    long long sum_values = 0;
    for (int i = 0; i < N; i++) {
        f >> I[i].value >> I[i].weight;
        if(f.fail()){
            std::cerr << "Invalid input." << std::endl;
            Clear();
            exit(1);
        }
        sum_weights += I[i].weight;
        sum_values += I[i].value;
    }
    f.close();

    // std::cout << "Total Weights: " << sum_weights << ", Total Values: " << sum_values << "\n";
    // if(sum_weights <= K){
    //     std::cout << "All items can be included without exceeding K.\n";
    // } else {
    //     std::cout << "Not all items can be included. Some items will need to be excluded.\n";
    // }
}

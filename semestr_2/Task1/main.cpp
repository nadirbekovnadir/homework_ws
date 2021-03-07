#include <iostream>

#include "Matrix.h"
#include "Solver.h"

#include <vector>

using namespace std;

int main(int, char **)
{
    vector<vector<float>> A_v = {{1, 0, 0, 0},
                                 {0, 1, 0, 0},
                                 {0, 0, 1, 0},
                                 {0, 0, 0, 1}};

    vector<vector<float>> B_v = {{1},
                                 {2},
                                 {3},
                                 {4}};

    Matrix<float> A(A_v);
    Matrix<float> B(B_v);

    Solver::Solve(A, B);

    std::cout << "Hello, world!\n";
}

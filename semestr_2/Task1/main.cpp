#include <iostream>

#include "Matrix.h"
#include "Solver.h"

#include <vector>

using namespace std;

void PrintAnswer(Matrix<float> X)
{
    for(int j = 0; j < X.Rows(); ++j)
    {
        for (int i = 0; i < X.Columns(); ++i)
            cout << X.Get(j, i) << "\t";

        cout << "\n";
    }
}

int main(int, char **)
{
    vector<vector<float>> A_v4 = {{1, 2, 0, 0},
                                  {2, 4, 3, 0},
                                  {0, 2, 0, 0},
                                  {0, 0, 0, 4}};

    vector<vector<float>> B_v4 = {{1},
                                  {1},
                                  {1},
                                  {1}};

    vector<vector<float>> A_v5 = {{1, 2, 3, 4},
                                  {5, 6, 7, 8},
                                  {9, 10, 11, 12},
                                  {13, 14, 15, 16}};

    vector<vector<float>> B_v5 = {{1},
                                  {1},
                                  {1},
                                  {1}};

    vector<vector<float>> A_v6 = {{1, 2, 3, 4},
                                  {-1, -2, 0, 3},
                                  {0, 6, 11, 2},
                                  {4, -2, 1, 0}};

    vector<vector<float>> B_v6 = {{5},
                                  {-2},
                                  {14},
                                  {4}};

    //Надо бы приделать initializer_list
    Matrix<float> A(A_v6);
    Matrix<float> B(B_v6);
    bool error = false;

    PrintAnswer(Solver::Solve(A, B, error));
    PrintAnswer(Solver::Reverse(A, error));

    if (error == true)
        cout << "Vyrozhdenaya";

    cout << endl;

    std::cout << "Hello, world!\n";
}

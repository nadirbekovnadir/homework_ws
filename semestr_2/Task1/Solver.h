#ifndef SOLVER_H
#define SOLVER_H

#include "Matrix.h"
#include <list>
#include <tuple>

class Solver
{
public:
    template <class T>
    static Matrix<T> Solve(const Matrix<T> &A, const Matrix<T> &B, bool &error);

    template <class T>
    static Matrix<T> Reverse(const Matrix<T> &A, bool &error);

private:
    template <class T>
    static bool ForwardMove(Matrix<T> &A, Matrix<T> &L);

    static list<tuple<int, int>> hist_rev;
    template <class T>
    static T Sort(Matrix<T> &A, Matrix<T> &L, int col);

    template <class T>
    static void ForwardSubstitution(const Matrix<T> &L, Matrix<T> &B);

    template <class T>
    static void BackwardSubstitution(const Matrix<T> &U, Matrix<T> &B);

    template <class T>
    static void Desort(Matrix<T> &X);
};

list<tuple<int, int>> Solver::hist_rev;

// ------------------ Public block ------------------ //

template <class T>
Matrix<T> Solver::Solve(const Matrix<T> &A, const Matrix<T> &B, bool &error)
{
    hist_rev.clear();

    Matrix<T> L(A.Rows(), A.Columns());
    Matrix<T> U(A);
    Matrix<T> X(B);

    error = !ForwardMove(U, L);
    Desort(X);

    ForwardSubstitution(L, X);
    BackwardSubstitution(U, X);

    return X;
}

template <class T>
Matrix<T> Solver::Reverse(const Matrix<T> &A, bool &error)
{
    hist_rev.clear();

    Matrix<T> E(A.Rows(), A.Columns());
    for (int i = 0; i < E.Rows(); ++i)
        E.Set(i, i, 1);

    return Solve(A, E, error);
}

// ------------------ Private block ------------------ //

template <class T>
bool Solver::ForwardMove(Matrix<T> &A, Matrix<T> &L)
{
    T m, temp;
    tuple<int, int> hist_elem;

    int i, j, k;
    for (i = 0; i < A.Rows(); ++i)
    {
        temp = Sort(A, L, i);
        //Проверка для вырожденности
        if ((temp < 0 ? -temp : temp) < std::numeric_limits<T>::epsilon() * 2) //Можно ввести коэфф нечувствительности
            return false;

        for (j = i + 1; j < A.Rows(); ++j)
        {
            m = A.Get(j, i) / temp;
            if (m == 0)
                continue;

            L.Set(j, i, m);

            for (k = 0; k < A.Columns(); ++k)
                A.Set(j, k, A.Get(j, k) - m * A.Get(i, k));
        }
    }

    for (i = 0; i < A.Rows(); ++i)
        L.Set(i, i, 1);

    return true;
}

template <class T>
static T Solver::Sort(Matrix<T> &A, Matrix<T> &L, int col)
{
    T max, temp;
    int swapI;

    int i;
    max = A.Get(col, col);
    max = max < 0 ? max * (-1) : max;
    swapI = col;

    for (i = col + 1; i < A.Rows(); ++i)
    {
        temp = A.Get(i, col);
        temp = temp < 0 ? temp * (-1) : temp;
        if (max >= temp)
            continue;

        max = temp;
        swapI = i;
    }

    if (swapI != col)
    {
        A.SwapRows(swapI, col);
        L.SwapRows(swapI, col);
        hist_rev.push_back(make_tuple(swapI, col));
    }

    return max;
}

template <class T>
void Solver::ForwardSubstitution(const Matrix<T> &L, Matrix<T> &B)
{
    T sum;
    int i, j, k;
    for (k = 0; k < B.Columns(); ++k)
    {
        B.Set(0, k, B.Get(0, k) / L.Get(0, 0));

        for (i = 1; i < B.Rows(); ++i)
        {
            sum = 0;
            for (j = 0; j < i; ++j)
                sum += L.Get(i, j) * B.Get(j, k);

            B.Set(i, k, (B.Get(i, k) - sum) / L.Get(i, i));
        }
    }
}

template <class T>
static void Solver::BackwardSubstitution(const Matrix<T> &U, Matrix<T> &B)
{
    T sum;
    int i, j, k;
    for (k = 0; k < B.Columns(); ++k)
    {
        B.Set(B.Rows() - 1, k, B.Get(B.Rows() - 1, k) / U.Get(B.Rows() - 1, B.Rows() - 1));

        for (i = B.Rows() - 2; i >= 0; --i)
        {
            sum = 0;
            for (j = i + 1; j < U.Columns(); ++j)
                sum += U.Get(i, j) * B.Get(j, k);

            B.Set(i, k, (B.Get(i, k) - sum) / U.Get(i, i));
        }
    }
}

template <class T>
static void Solver::Desort(Matrix<T> &X)
{
    for (auto iter = hist_rev.begin(); iter != hist_rev.end(); ++iter)
        X.SwapRows(get<0>(*iter), get<1>(*iter));
}

#endif
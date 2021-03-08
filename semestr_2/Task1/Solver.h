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
    static Matrix<T> Reverse(const Matrix<T> &A, const Matrix<T> &B, bool &error);

private:
    template <class T>
    static bool ForwardMove(Matrix<T> &A, Matrix<T> &L);

    static list<tuple<int, int>> hist_rev;
    template <class T>
    static T Sort(Matrix<T> &A, Matrix<T> &L, int col);

    template <class T>
    static void BackwardMove(const Matrix<T> &A, const Matrix<T> &B, Matrix<T> &X);

    template <class T>
    static void Desort(Matrix<T> &X);
};

list<tuple<int, int>> Solver::hist_rev;

// ------------------ Public block ------------------ //

template <class T>
Matrix<T> Solver::Solve(const Matrix<T> &A, const Matrix<T> &B, bool &error)
{
    hist_rev.clear();

    Matrix<T> X(B.Rows(), B.Columns());
    Matrix<T> U(A);
    Matrix<T> L(A.Rows(), A.Columns());
    Matrix<T> B_des(B);

    error = !ForwardMove(U, L);
    Desort(B_des);
    BackwardMove(U, L * B_des, X);

    return X;
}

template <class T>
Matrix<T> Solver::Reverse(const Matrix<T> &A, const Matrix<T> &B, bool &error)
{
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

            L.Set(j, i, -m);

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
static void Solver::BackwardMove(const Matrix<T> &A, const Matrix<T> &B, Matrix<T> &X)
{
    int i, j;
    T sum = 0;
    X.Set(X.Rows() - 1, 0, B.Get(X.Rows() - 1, 0) / A.Get(X.Rows() - 1, X.Rows() - 1));

    for (i = X.Rows() - 2; i >= 0; --i)
    {
        for (j = i + 1; j < A.Columns(); ++j)
            sum += A.Get(i, j) * X.Get(j, 0);

        X.Set(i, 0, (B.Get(i, 0) - sum) / A.Get(i, i));
    }
}

template <class T>
static void Solver::Desort(Matrix<T> &X)
{
    for (auto iter = hist_rev.begin(); iter != hist_rev.end(); ++iter)
        X.SwapRows(get<0>(*iter), get<1>(*iter));
}

#endif
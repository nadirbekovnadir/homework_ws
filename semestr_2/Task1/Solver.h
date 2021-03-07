#ifndef SOLVER_H
#define SOLVER_H

#include "Matrix.h"

class Solver
{
public:
    template <class T>
    static Matrix<T> Solve(const Matrix<T> &A, const Matrix<T> &B);

private:
    template <class T>
    static Matrix<T> Prepare(Matrix<T> A);

    template <class T>
    static Matrix<T> ForwardMove(const Matrix<T> &m1, const Matrix<T> &m2);

    template <class T>
    static Matrix<T> CreateL(const Matrix<T> &A);

    template <class T>
    static Matrix<T> CreateU(const Matrix<T> &L, const Matrix<T> &A);
};

template <class T>
Matrix<T> Solver::Solve(const Matrix<T> &A, const Matrix<T> &B)
{
    Matrix<T> prepA(Prepare(A));
    Matrix<T> L(CreateL(prepA));
    Matrix<T> U(CreateU(L, prepA));

    Matrix<T> B_new(ForwardMove(L, B));
    B_new = ForwardMove(U, B_new);

    return B_new;
}

template <class T>
Matrix<T> Solver::Prepare(Matrix<T> A)
{
    Matrix<T> result(A.Rows(), A.Columns());
    T max;
    int currI;

    int i, j;
    for (j = 0; j < A.Columns(); ++j)
    {
        max = A.Get(j, j);
        currI = j;
        for (i = j + 1; i < A.Rows(); ++i)
        {
            if (A.Get(i, j) <= max)
                continue;

            max = A.Get(i, j);
            currI = i;
        }

        A.SwapRows(i, currI);
    }

    return result;
}

template <class T>
Matrix<T> Solver::ForwardMove(const Matrix<T> &A, const Matrix<T> &B)
{
    Matrix<T> X(B.Rows(), 1);

    int i, j;
    T sum = 0;
    X.Set(X.Rows() - 1, 1, B.Get(X.Rows() - 1, 1) / A.Get(X.Rows() - 1, X.Rows() - 1));

    for (i = X.Rows() - 2; i >= 0; --i)
    {
        for (j = i + 1; j < A.Columns(); ++j)
            sum += A.Get(i, j) * X.Get(j, 1);

        X.Set(i, 1, (B.Get(i, 1) - sum) / A.Get(i, i));
    }

    return X;
}

template <class T>
Matrix<T> Solver::CreateL(const Matrix<T> &A)
{
    Matrix<T> L(A.Rows(), A.Columns());

    int i, j;
    T temp1, temp2;
    for (j = 0; j < L.Columns(); ++j)
    {
        L.Set(j, j, 1);
        temp1 = A.Get(j, j);
        for (i = j + 1; i < L.Rows(); ++i)
        {
            temp2 = A.Get(i, j);
            L.Set(i, j, temp2 / temp1);
        }
    }

    return L;
}

template <class T>
Matrix<T> Solver::CreateU(const Matrix<T> &L, const Matrix<T> &A)
{
    Matrix<T> U(A.Columns(), A.Rows());

    int i, j;
    for (j = 0; j < U.Columns(); ++j)
    {
        U.Set(j, j, 1);
        for (i = j + 1; i < U.Rows(); ++i)
            U.Set(i, j, -L.Get(i, j));
    }

    A * 2;

    return U;
}


#endif
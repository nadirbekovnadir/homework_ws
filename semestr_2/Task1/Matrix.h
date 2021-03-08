#ifndef MATRIX_H
#define MATRIX_H

#include "vector"

using namespace std;

template <class T>
class Matrix
{

private:
    vector<vector<T> *> m_matrix;

    int m_columns = 0;
    int m_rows = 0;

public:
    Matrix(int n, int m)
    {
        m_columns = m;
        m_rows = n;
        m_matrix.resize(m_rows);

        for (int i = 0; i < n; ++i)
            m_matrix[i] = new vector<T>(m);
    }

    Matrix(const Matrix<T> &m)
    {
        m_columns = m.m_columns;
        m_rows = m.m_rows;
        m_matrix.resize(m_rows);

        for (int i = 0; i < m_rows; ++i)
            m_matrix[i] = new vector<T>(*m.m_matrix[i]);
    }

    Matrix(vector<vector<T>> values)
    {
        m_columns = values.begin()->size();
        m_rows = values.size();
        m_matrix.resize(m_rows);

        for (int i = 0; i < m_rows; ++i)
            m_matrix[i] = new vector<T>(values[i]);
    }

    ~Matrix()
    {
        cout << "Matrix Deleted" << endl;
        for (int i = 0; i < m_rows; ++i)
            delete m_matrix[i];
    }

    T Get(int n, int m) const
    {
        return (*m_matrix[n])[m];
    }

    void Set(int n, int m, T value)
    {
        (*m_matrix[n])[m] = value;
    }

    void Set(vector<vector<T>> values)
    {
        for (int i = 0; i < m_rows; ++i)
            m_matrix[i] = new vector<T>(values[i]);
    }

    void SwapRows(int i, int j)
    {
        if (i == j)
            return;

        auto temp = m_matrix[i];
        m_matrix[i] = m_matrix[j];
        m_matrix[j] = temp;
    }

    int Rows() const
    {
        return m_rows;
    }

    int Columns() const
    {
        return m_columns;
    }

    Matrix<T> operator*(const Matrix<T> &other) const
    {
        Matrix<T> res(this->Rows(), other.Columns());
        T sum;

        int i, j, k;
        for (i = 0; i < m_rows; ++i)
        {
            for (j = 0; j < other.Columns(); ++j)
            {
                sum = 0;
                for (k = 0; k < m_columns; ++k)
                    sum += this->Get(i, k) * other.Get(k, j);

                res.Set(i, j, sum);
            }
        }

        return res;
    }

    Matrix<T> operator*(T other) const
    {
        Matrix<T> res(this->Rows(), this->Columns());

        int i, j;
        for (i = 0; i < m_rows; ++i)
            for (j = 0; j < m_columns; ++j)
                res.Set(i, j, res.Get(i, j) * other);

        return res;
    }

    Matrix<T> &operator=(const Matrix<T> &other)
    {
        m_columns = other.m_columns;
        m_rows = other.m_rows;

        for (int i = 0; i < m_rows; ++i)
            *m_matrix[i] = *other.m_matrix[i];

        return *this;
    }
};

#endif
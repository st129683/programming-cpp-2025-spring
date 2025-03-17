#pragma once
#include <ostream>

class Matrix
{
private:
    double** data;
    int rows;
    int cols;
    double** createData(int rows, int cols);
    void freeData(double** data, int rows);

public:
    Matrix();
    Matrix(int dim);
    Matrix(int rows, int cols);
    Matrix(const Matrix& matr);
    ~Matrix();
    double get(int row, int col);
    void set(int row, int col, double val);
    int getR();
    int getC();
    void print(std::ostream& stream);
    void multBy(double k);
    void addTo(Matrix matr);
    void transpose();
    double det();
    Matrix minor(int row, int col);
    friend Matrix add(Matrix m1, Matrix m2);
    friend Matrix transpose(Matrix m);
    friend Matrix subtr(Matrix m1, Matrix m2);
    friend Matrix mult(Matrix m1, Matrix m2);
    friend Matrix reverse(Matrix m);
    friend Matrix solve(Matrix A, Matrix B);
};
#pragma once
#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__
#include <vector>

class Matrix {

public:
    Matrix() { };
    Matrix(int row_, int col_);
    Matrix(const Matrix& m);
    Matrix(int row_, int col_, const std::vector<double>& arr);
    Matrix(const std::vector<std::vector<double>>& arr);
    ~Matrix();


    void setArray(const std::vector<std::vector<double>>& arr);
    void setRandom(int lim);
    void setZreo(void);
    void setmax(const double& lim);
    void setgeq(const double& lim);

    const std::vector<std::vector<double>> getArray(void) const;
    void putArray() const;
    void putshape() const;
    unsigned int getRow(void) const;
    unsigned int getCol(void) const;

    Matrix T(void) const;

    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m) const;
    Matrix operator-(const Matrix& m) const;
    Matrix operator*(const Matrix& m) const;
    Matrix operator^(const Matrix& m) const;
    Matrix operator*(const double& scalar) const;
    Matrix operator/(const double& scalar) const;
    Matrix operator-(const double& scalar) const;
    Matrix operator+(const double& scalar) const;
    Matrix operator-(void) const;
private:
    int rows;
    int cols;
    std::vector<std::vector<double>> arr;
};

#endif

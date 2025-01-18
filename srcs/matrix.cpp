#include <iostream>
#include <string.h>
#include <random>

#include "matrix.hpp"

std::random_device rd;
std::mt19937_64 gen(rd());


Matrix::Matrix(int row_, int col_) : rows(row_), cols(col_) {
    if (rows == 0 || cols == 0) {
        return;
    }
    arr.resize(rows);

    for (int i = 0; i < rows; i++) {
        arr[i].resize(cols);
    }

}

Matrix::Matrix(const Matrix& m) {
    rows = m.rows;
    cols = m.cols;
    arr = m.arr;
}

Matrix::Matrix(int row_, int col_, const std::vector<double>& arr_) {
    rows = row_; cols = col_;
    if (rows == 0 || cols == 0) {
        return;
    }
    arr.resize(rows);
    for (int i = 0; i < rows; i++) {
        arr[i].resize(cols);
    }

    int p = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (p >= arr_.size()) {
                return;
            }
            arr[i][j] = arr_[p++];
        }

    }
}

Matrix::Matrix(const std::vector<std::vector<double>>& arr_) {
    rows = arr_.size();
    cols = arr_[0].size();
    arr = arr_;
}


Matrix::~Matrix() {
    // std::cout << "~Matrix called" << std::endl;
    // print();
}


void Matrix::setArray(const std::vector<std::vector<double>>& arr_) {
    if (rows != arr_.size() || cols != arr_[0].size()) {
        std::cerr << "Matrix::setArray: size not equal" << std::endl;
        return;
    }
    arr = arr_;
}

void Matrix::setRandom(int lim) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = gen() % lim;
        }
    }
}

void Matrix::setZreo(void) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = 0;
        }
    }
}

void Matrix::setmax(const double& lim) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = arr[i][j] > lim ? arr[i][j] : lim;
        }
    }
}

void Matrix::setgeq(const double& lim) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            arr[i][j] = arr[i][j] >= lim ? 1 : 0;
        }
    }
}

const std::vector<std::vector<double>> Matrix::getArray(void) const {
    return arr;
}

void Matrix::putshape() const {
    std::cout << "rows:" << rows << " cols:" << cols << std::endl;
}

void Matrix::putArray() const {
    std::cout << "rows:" << rows << " cols:" << cols << std::endl;
    for (int i = 0; i < rows; i++) {
        std::cout << i << ": [";
        for (int j = 0; j < cols - 1; j++) {
            std::cout << arr[i][j] << ", ";
        }
        std::cout << arr[i][cols - 1] << "]" << std::endl;
    }
}


unsigned int Matrix::getRow(void) const {
    return rows;
}

unsigned int Matrix::getCol(void) const {
    return cols;
}

Matrix& Matrix::operator=(const Matrix& m) {
    rows = m.rows;
    cols = m.cols;
    arr = m.arr;
    return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) {
        std::cerr << "Matrix::operator+: size not equal" << std::endl;
        return Matrix(0, 0);
    }

    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] + m.arr[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) {
        std::cerr << "Matrix::operator-: size not equal" << std::endl;
        return Matrix(0, 0);
    }

    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] - m.arr[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
    if (cols != m.rows) {
        std::cerr << "Matrix::operator*: size not equal" << std::endl;
        return Matrix(0, 0);
    }

    Matrix res(rows, m.cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < m.cols; j++) {
            res.arr[i][j] = 0;
            for (int k = 0; k < cols; k++) {
                res.arr[i][j] += arr[i][k] * m.arr[k][j];
            }
        }
    }
    return res;
}

Matrix Matrix::operator*(const double& scalar) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] * scalar;
        }
    }
    return res;
}

Matrix Matrix::operator^(const Matrix& m) const {
    if (rows != m.rows || cols != m.cols) {
        std::cerr << "Matrix::operator^: size not equal" << std::endl;
        return Matrix(0, 0);
    }

    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] * m.arr[i][j];
        }
    }
    return res;
}

Matrix Matrix::operator/(const double& scalar) const {
    Matrix res(rows, cols);
    if (scalar == 0) {
        std::cerr << "Matrix::operator/: scalar is zero" << std::endl;
        return Matrix(0, 0);
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] / scalar;
        }
    }
    return res;
}

Matrix Matrix::operator-(const double& scalar) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] - scalar;
        }
    }
    return res;
}

Matrix Matrix::operator+(const double& scalar) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = arr[i][j] + scalar;
        }
    }
    return res;
}

Matrix Matrix::operator-(void) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res.arr[i][j] = -arr[i][j];
        }
    }
    return res;
}

Matrix Matrix::T(void) const {
    Matrix res(cols, rows);
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            res.arr[i][j] = arr[j][i];
        }
    }
    return res;
}

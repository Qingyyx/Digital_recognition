#pragma once
#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__

#include "matrix.hpp"

#include <functional>

class Network {

public:
    Network(std::vector<unsigned int> layer_node_num);
    ~Network() { };

    void setLr(const double& lr);
    void setActivateFunc(const std::function<Matrix(const Matrix&)>& f);
    void setUpdateWeightFunc(const std::function<Matrix(const Matrix&)>& f);
    void putConfig();

    std::vector<double> forward(const Matrix& train_data);
    void backward(Matrix pred, Matrix real);

    double compute_loss(const std::vector<double>& pred, const std::vector<double>& real);

private:
    double lr;
    std::vector<unsigned int> layer_node_num;
    std::vector<Matrix> weights;
    std::vector<Matrix> biases;
    std::vector<Matrix> loss;
    std::vector<Matrix> inputs;
    std::vector<Matrix> activations;

    std::function<Matrix(const Matrix&)> activate_func;
    std::function<Matrix(const Matrix&)> activate_derivative_func;

    std::vector<double> softmax(const std::vector<double>& x);

    unsigned int layer_num;

};

#endif

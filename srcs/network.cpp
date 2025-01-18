
#include <iostream>
#include <math.h>

#include "matrix.hpp"
#include "network.hpp"

const double eps = 1e-12;

Network::Network(std::vector<unsigned int> layer_node_num) {
    this->layer_node_num = layer_node_num;
    layer_num = layer_node_num.size();
    if (layer_num < 2) {
        std::cerr << "layer_num is " << layer_node_num.size() << "min=2" << std::endl;
        return;
    }

    for (auto number : layer_node_num) {
        if (number <= 0) {
            std::cerr << "layer_node_num is " << number << "min=1" << std::endl;
            return;
        }
    }

    inputs.resize(layer_num);
    activations.resize(layer_num);
    weights.reserve(layer_num);
    biases.reserve(layer_num);
    for (int i = 1; i < layer_num; ++i) {
        Matrix m(layer_node_num[i - 1], layer_node_num[i]);
        m.setRandom(10000);
        m = m / 10000;
        weights[i] = m;
        Matrix n(1, layer_node_num[i]);
        n.setRandom(10000);
        n = n / 10000;
        biases[i] = n;
    }
}

void Network::setLr(const double& lr) {
    this->lr = lr;
}
void Network::setActivateFunc(const std::function<Matrix(const Matrix&)>& f) {
    activate_func = f;
}
void Network::setUpdateWeightFunc(const std::function<Matrix(const Matrix&)>& f) {
    activate_derivative_func = f;
}

void Network::putConfig() {
    std::cout << "=====================================" << std::endl;
    std::cout << "network config:" << std::endl;
    std::cout << "learning rate: " << lr << std::endl;
    std::cout << "total layer num: " << layer_num << std::endl;
    for (int i = 0; i < layer_num; ++i) {
        std::cout << "nodes num of layer" << i << ": " << layer_node_num[i] << std::endl;
        for (auto& m : weights) {
            m.putArray();
        }
    }
    std::cout << "=====================================" << std::endl;
}

std::vector<double> Network::softmax(const std::vector<double>& x) {
    std::vector<double> exp_x;
    double sum = 0;
    for (auto& i : x) {
        exp_x.push_back(exp(i));
        sum += exp(i);
    }
    for (auto& i : exp_x) {
        i /= sum;
    }
    return exp_x;
}


std::vector<double> Network::forward(const Matrix& train_data) {
    activations[0] = train_data;
    for (int i = 1; i < layer_num; ++i) {
        inputs[i] = activations[i - 1] * weights[i] + biases[i];
        inputs[i] = inputs[i] / (double)layer_node_num[i - 1];
        activations[i] = activate_func(inputs[i]);      // 激活函数以后的值
        // activations[i].putArray();
    }
    if (inputs.back().getRow() != 1) {
        throw std::runtime_error("inputs.back().getRow() != 1");
    }
    return softmax(inputs.back().getArray()[0]);
}

double Network::compute_loss(const std::vector<double>& pred, const std::vector<double>& real) {
    for (int i = 0; i < 10; i++) {
        if (real[i] > eps)
            return -log(pred[i] + eps);
    }
    throw std::runtime_error("The format of the real is incorrect");
    return -1;
}


void Network::backward(Matrix pred, Matrix real) {
    Matrix d_loss = pred - real;        // softmax + cross entropy
    for (int i = layer_num - 1; i > 0; --i) {
        Matrix d_activation = d_loss;
        if (i != layer_num - 1) {
            // std::cerr << "d_loss = "; d_loss.putshape();
            // std::cerr << "inputs[i + 1] = "; inputs[i].putshape();
            d_activation = d_loss ^ activate_derivative_func(inputs[i]);  // 下一层到这层的链式求导
        }
        // std::cerr << "d_activation = "; d_activation.putshape();
        Matrix d_weights = activations[i - 1].T() * d_activation;
        // std::cerr << "d_weights = "; d_weights.putshape();
        // Matrix d_biases = np.sum(d_activation, axis = 0);
        Matrix d_biases = d_activation;
        // std::cerr << "d_biases = "; d_biases.putshape();
        // std::cerr << "weights[i] = "; weights[i].putshape();
        d_loss = d_activation * weights[i].T();

        // std::cerr << "reach it\n";
        weights[i] = weights[i] - d_weights * lr;
        biases[i] = biases[i] - d_biases * lr;
    }
}

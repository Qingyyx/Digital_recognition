
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "network.hpp"
#include "matrix.hpp"

signed main(const int argc, const char* argv[]) {
    const double lr = 0.1;
    std::vector<unsigned int> layer_node_num = {784, 256, 10};

    std::string train_file = "../mnist_dataset/mnist_train.csv";
    std::string test_file = "../mnist_dataset/mnist_test.csv";

    clock_t c1 = clock(), c2, c3;

    Network net(layer_node_num);
    net.setLr(lr);

    std::ifstream train_data(train_file);
    std::ifstream test_data(test_file);

    if (!train_data.is_open() || !test_data.is_open()) {
        std::cerr << "Error opening file(s)." << std::endl;
        return -1;
    }

    // 这里就不用epoch了，所有训练数据分别训练一次

    auto ont_hot = [](int label) -> std::vector<double> {
        std::vector<double> result(10, 0);
        result[label] = 1;
        return result;
    };
    auto ReLU = [](const Matrix& x) -> Matrix {
        Matrix result(x);
        result.setmax(0);
        return result;
    };
    auto ReLU_derivative = [](const Matrix& x) -> Matrix {
        Matrix result(x);
        result.setgeq(0);
        return result;
    };

    net.setActivateFunc(ReLU);
    net.setUpdateWeightFunc(ReLU_derivative);

    int tim = 0;

    std::string line;
    std::getline(train_data, line);
    while (std::getline(train_data, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<double> input;
        int label;

        std::getline(ss, value, ',');
        label = std::stoi(value);

        while (std::getline(ss, value, ',')) {
            input.push_back(std::stod(value) / 255.0); // Normalize the grayscale value
        }

        std::vector<double> real = ont_hot(label);
        std::vector<double> pred = net.forward(Matrix(1, input.size(), input));
        // printf("pred: "); for (auto& i : pred) printf("%f ", i); printf("\n");
        // printf("real: "); for (auto& i : real) printf("%f ", i); printf("\n");
        if (++tim % 1000 == 0) {
            double loss = net.compute_loss(pred, real);
            printf("loss: %f\n", loss);
        }
        net.backward(Matrix(1, pred.size(), pred), Matrix(1, real.size(), real));
        // if (++tim > 1000) break;
    }
    c2 = clock();
    std::cout << "trans time used: " << (double)(c2 - c1) / CLOCKS_PER_SEC << "s" << std::endl;

    int total = 0, correct = 0;
    std::getline(test_data, line);
    while (std::getline(test_data, line)) {
        std::stringstream ss(line);
        std::string value;
        std::vector<double> input;
        int label;

        std::getline(ss, value, ',');
        label = std::stoi(value);

        while (std::getline(ss, value, ',')) {
            input.push_back(std::stod(value) / 255.0); // Normalize the grayscale value
        }

        std::vector<double> real = ont_hot(label);
        std::vector<double> pred = net.forward(Matrix(1, input.size(), input));
        int prediction = std::max_element(pred.begin(), pred.end()) - pred.begin();
        if (prediction == label) {
            correct++;
            std::cout << "\033[32m"; // Set text color to green
        } else {
            std::cout << "\033[31m"; // Set text color to red
        }
        total++;
        printf("pred: "); for (auto& i : pred) printf("%f ", i); printf("\n");
        printf("[prediction : %d]", prediction);
        printf("[real: %d]\n", label);
        printf("accuracy: %f\n", (double)correct / total);
    }
    c3 = clock();
    std::cout << "test time used: " << (double)(c3 - c2) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << "total time used: " << (double)(c3 - c1) / CLOCKS_PER_SEC << "s" << std::endl;

    train_data.close();
    test_data.close();


}

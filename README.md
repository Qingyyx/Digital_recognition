# Digital Recognition(c++)

这是一个C++实现使用神经网络进行手写数字识别的项目。该项目使用MNIST数据集进行训练和测试。

因为某些原因，每次训练都只用一个图进行训练，可能导致代码效率低下，并且没有`bs`和`epoch`，把每个训练数据全都训练一次即完成。可能导致某个分类猜测概率更大等。实际准确率可以接受。

可以通过修改`network.cpp`里对最后一层的处理，使得一次能处理批量数据。

为了防止输出过多，`loss`没1000个数据输出一次，不是平均，每次结果根据数据有一定随机性，仅供参考。


## 依赖

- C++17
- CMake
- GNU Make

## 编译和运行

### 使用Makefile

1. 编译项目：

    ```sh
    make
    ```

2. 运行可执行文件：

    ```sh
    ./demo/demo_app
    ```

### 使用CMake

1. 创建构建目录并进入：

    ```sh
    mkdir build
    cd build
    ```

2. 生成Makefile：

    ```sh
    cmake ..
    ```

3. 编译项目：

    ```sh
    make
    ```

4. 运行可执行文件：

    ```sh
    ./Digital_recognition
    ```

## 数据集

请确保MNIST数据集文件 `mnist_train.csv` 和 `mnist_test.csv` 位于 mnist_dataset 目录中。并且终端所在位置能正确找到文件。否则会有报错：`Error opening file(s).`


## 结果

以下是某一次跑出来的结果：

- 准确率：93.88%
- 测试时间：23.2834秒
- 总时间：864.775秒

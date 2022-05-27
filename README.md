# VitisHLS_LeNet

## 1. Project Structure

`LeNet` folder contains a Vitis HLS project. `Lenet/test` folder stores testbench files and corresponding test data. `LeNet.ipynb` is a python jupyter notebook file where you can find model definition, MNIST dataset, testbench data generation and so on.

```c
.
|-- LICENSE
|-- LeNet
|   |-- 0
|   |-- hls.app
|   |-- release_sln
|   |-- src                 // source files
|   |   |-- LeNet.cpp
|   |   |-- avgpool_layer2.cpp
|   |   |-- avgpool_layer4.cpp
|   |   |-- common.cpp
|   |   |-- common.h
|   |   |-- conv2d_layer1.cpp
|   |   |-- conv2d_layer3.cpp
|   |   `-- dense_layer5.cpp
|   |-- test                // testbench files
|   |   |-- LeNet_tb.cpp
|   |   |-- LeNet_tb_data.txt
|   |   |-- LeNet_weights.txt
|   |   |-- avgpool_layer2_output.txt
|   |   |-- avgpool_layer2_tb.cpp
|   |   |-- avgpool_layer4_output.txt
|   |   |-- avgpool_layer4_tb.cpp
|   |   |-- common.h
|   |   |-- conv2d_layer1_output.txt
|   |   |-- conv2d_layer1_tb.cpp
|   |   |-- conv2d_layer3_output.txt
|   |   |-- conv2d_layer3_tb.cpp
|   |   |-- dense_layer5_output.txt
|   |   |-- dense_layer5_tb.cpp
|   |   |-- main_tb.cpp
|   |   |-- mnist_test_0_100.txt
|   |   `-- mnist_test_0_1000.txt
|   `-- vitis_hls.log
|-- LeNet.ipynb          // LeNet model, test data generation and so on
`-- README.md
```

## 2. Suggestions

1. It's recommended to change the `LENET_TEST_CASES` macro in `Lenet/test/common.h` to a much smaller value (< 10) before doing Cosimulation in Vitis HLS.
2. This design didn't consider any interface issues.

## 3. C Simulation Results

![C Simulation Results](https://s1.328888.xyz/2022/05/27/thah2.png)

## 4. C Synthesis Results

![C Synthesis Results](https://s1.328888.xyz/2022/05/27/thKPT.png)

## 5. Reference

<a id="ref_1">[[1]王小雪. 基于FPGA的卷积神经网络手写数字识别系统的实现[D].北京理工大学,2016. ](https://kns.cnki.net/kcms/detail/detail.aspx?dbcode=CMFD&dbname=CMFD201801&filename=1018812356.nh) </a >

<a id="ref_2">[[2]Zhang A, Lipton Z C, Li M, et al. Dive into deep learning[J]. arXiv preprint arXiv:2106.11342, 2021.](https://zh.d2l.ai/index.html) </a >

<a id="ref_3">[[3]HLS学习笔记——实现卷积层的加速计算](https://blog.csdn.net/qq_36334929/article/details/108627123) </a >

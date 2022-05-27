############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
open_project LeNet
set_top LeNet
add_files LeNet/src/LeNet.cpp
add_files LeNet/src/avgpool_layer2.cpp
add_files LeNet/src/avgpool_layer4.cpp
add_files LeNet/src/common.cpp
add_files LeNet/src/common.h
add_files LeNet/src/conv2d_layer1.cpp
add_files LeNet/src/conv2d_layer3.cpp
add_files LeNet/src/dense_layer5.cpp
add_files -tb LeNet/test/LeNet_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/LeNet_weights.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/avgpool_layer2_output.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/avgpool_layer2_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/avgpool_layer4_output.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/avgpool_layer4_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/common.h -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/conv2d_layer1_output.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/conv2d_layer1_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/conv2d_layer3_output.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/conv2d_layer3_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/dense_layer5_output.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/dense_layer5_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/main_tb.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/mnist_test_0_100.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
add_files -tb LeNet/test/mnist_test_0_1000.txt -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "release_sln" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 10 -name default
config_export -display_name LeNet -format ip_catalog -output D:/Project/FPGA/HLS/IP -rtl verilog
source "./LeNet/release_sln/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level port
export_design -rtl verilog -format ip_catalog -output D:/Project/FPGA/HLS/IP

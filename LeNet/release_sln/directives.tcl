############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_top -name LeNet "LeNet"
set_directive_array_partition -type complete -dim 1 "conv2d_layer1" image_data
set_directive_array_partition -type complete -dim 1 "conv2d_layer1" layer1_output
set_directive_array_partition -type complete -dim 1 "conv2d_layer1" kernel_weight
set_directive_array_partition -type complete -dim 1 "avgpool_layer2" layer1_output
set_directive_array_partition -type complete -dim 1 "avgpool_layer2" layer2_output
set_directive_pipeline "avgpool_layer2/loop_output_channel"
set_directive_array_partition -type complete -dim 1 "conv2d_layer3" layer2_output
set_directive_array_partition -type complete -dim 1 "conv2d_layer3" kernel_weight
set_directive_array_partition -type complete -dim 1 "conv2d_layer3" layer3_output
set_directive_array_partition -type complete -dim 2 "conv2d_layer3" kernel_weight
set_directive_pipeline "avgpool_layer4/loop_output_channel"
set_directive_pipeline "dense_layer5/loop"

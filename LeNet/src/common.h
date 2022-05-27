#ifndef COMMON_H_
#define COMMON_H_
#include "ap_fixed.h"

typedef ap_fixed<16,6, AP_RND> fixed_t;
//typedef float fixed_t;

typedef struct dense_param_s
{
	fixed_t weight_arr[192*10];
	fixed_t bias_arr[10];
}dense_param_t;


fixed_t sigmoid(fixed_t x);
void conv2d_layer1(fixed_t image_data[28][28], fixed_t kernel_weight[3][5][5],
		fixed_t kernel_bias[3],fixed_t layer1_output[3][24][24]);
void avgpool_layer2(fixed_t layer1_output[3][24][24], fixed_t layer2_output[3][12][12]);
void conv2d_layer3(fixed_t layer2_output[3][12][12], fixed_t kernel_weight[12][3][5][5],
		fixed_t kernel_bias[12], fixed_t layer3_output[12][8][8]);
void avgpool_layer4(fixed_t layer3_output[12][8][8], fixed_t layer4_output[12][4][4]);
void dense_layer5(fixed_t layer4_output[12][4][4], dense_param_t &dense_param, fixed_t layer5_output[10]);
short LeNet(fixed_t image_data[28*28], fixed_t param_arr[2944]);

#endif

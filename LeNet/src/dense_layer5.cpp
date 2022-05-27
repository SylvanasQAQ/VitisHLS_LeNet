#include "common.h"
#include <iostream>
using namespace std;

void dense_layer5(fixed_t layer4_output[12][4][4], dense_param_t &dense_param, fixed_t layer5_output[10])
{
	fixed_t layer4_flatten[12*4*4];
	int offset = 0, k_in, r, c;

	for(r = 0; r < 4; r++)
		for(c = 0; c < 4; c++)
			for(k_in = 0; k_in < 12; k_in++)
				layer4_flatten[offset++] = layer4_output[k_in][r][c];

	for(r = 0; r < 10; r++)
		layer5_output[r] = 0;

	for(r = 0; r < 192; r++)
		loop:
		for(c = 0; c < 10; c++)
			layer5_output[c] = layer5_output[c] + dense_param.weight_arr[r*10+c] * layer4_flatten[r];

	for(r = 0; r < 10; r++)
		layer5_output[r] += dense_param.bias_arr[r];
}

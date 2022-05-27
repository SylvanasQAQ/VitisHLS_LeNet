#include "common.h"

void conv2d_layer3(fixed_t layer2_output[3][12][12], fixed_t kernel_weight[12][3][5][5],
		fixed_t kernel_bias[12], fixed_t layer3_output[12][8][8])
{
	int r, c, kr, kc, k_in, k_out;

	for(kr = 0; kr < 8; kr++)
		for(kc = 0; kc < 8; kc++)
			loop_output_channel_init:
			for(k_out = 0; k_out < 12; k_out++)
				layer3_output[k_out][kr][kc] = 0;

	kernel_row:
	for(kr = 0; kr < 5; kr++)
		kernel_column:
		for(kc = 0; kc < 5; kc++)
			loop_row:
			for(r = 0; r < 8; r++)
				loop_column:
				for(c = 0; c < 8; c++)
					loop_output_channel:
					for(k_out = 0; k_out < 12; k_out++)
						loop_input_channel:
						for(k_in = 0; k_in < 3; k_in++)
							layer3_output[k_out][r][c] +=
									layer2_output[k_in][r+kr][c+kc] * kernel_weight[k_out][k_in][kr][kc];

	for(r = 0; r < 8; r++)
		for(c = 0; c < 8; c++)
			loop_output_channel_final:
			for(k_out = 0; k_out < 12; k_out++)
				layer3_output[k_out][r][c] = sigmoid(layer3_output[k_out][r][c] + kernel_bias[k_out]);
}

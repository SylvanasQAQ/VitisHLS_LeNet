#include "common.h"

void conv2d_layer1(fixed_t image_data[28][28], fixed_t kernel_weight[3][5][5],
		fixed_t kernel_bias[3],fixed_t layer1_output[3][24][24])
{
	int r, c, kr, kc, k;

	for(kr = 0; kr < 24; kr++)
		for(kc = 0; kc < 24; kc++)
			loop_output_channel_init:
			for(k = 0; k < 3; k++)
				layer1_output[k][kr][kc] = 0;

	kernel_row:
	for(kr = 0; kr < 5; kr++)
		kernel_column:
		for(kc = 0; kc < 5; kc++)
			loop_row:
			for(r = 0; r < 24; r++)
				loop_column:
				for(c = 0; c < 24; c++)
					loop_output_channel:
					for(k = 0; k < 3; k++)
						layer1_output[k][r][c] +=
								image_data[r+kr][c+kc] * kernel_weight[k][kr][kc];

	for(r = 0; r < 24; r++)
		for(c = 0; c < 24; c++)
			loop_output_channel_final:
			for(k = 0; k < 3; k++)
				layer1_output[k][r][c] = sigmoid(layer1_output[k][r][c] + kernel_bias[k]);

}

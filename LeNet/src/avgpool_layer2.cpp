#include "common.h"

void avgpool_layer2(fixed_t layer1_output[3][24][24], fixed_t layer2_output[3][12][12])
{
	int c, r, kc, kr, k_out;

	for(r = 0; r < 12; r++)
			for(c = 0; c < 12; c++)
				for(k_out = 0; k_out < 3; k_out++)
					layer2_output[k_out][r][c] = 0;

	for(kr = 0; kr < 2; kr++)
		kernel_column:
		for(kc = 0; kc < 2; kc++)
			loop_row:
			for(r = 0; r < 12; r++)
				loop_column:
				for(c = 0; c < 12; c++)
					loop_output_channel:
					for(k_out = 0; k_out < 3; k_out++)
						layer2_output[k_out][r][c] += layer1_output[k_out][r*2+kr][c*2+kc] * fixed_t(0.25);
}

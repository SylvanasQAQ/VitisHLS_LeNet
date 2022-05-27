#include "common.h"

void avgpool_layer4(fixed_t layer3_output[12][8][8], fixed_t layer4_output[12][4][4])
{
	int c, r, kc, kr, k_out;

	for(r = 0; r < 4; r++)
		for(c = 0; c < 4; c++)
			for(k_out = 0; k_out < 12; k_out++)
				layer4_output[k_out][r][c] = 0;

	for(kr = 0; kr < 2; kr++)
		kernel_column:
		for(kc = 0; kc < 2; kc++)
			loop_row:
			for(r = 0; r < 4; r++)
				loop_column:
				for(c = 0; c < 4; c++)
					loop_output_channel:
					for(k_out = 0; k_out < 12; k_out++)
						layer4_output[k_out][r][c] += layer3_output[k_out][r*2+kr][c*2+kc] * fixed_t(0.25);
}

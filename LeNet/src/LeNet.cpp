#include "common.h"

short LeNet(fixed_t image_data[28*28], fixed_t param_arr[2944])
{
	fixed_t kernel_weight_layer1[3][5][5], kernel_bias_layer1[3];
	fixed_t kernel_weight_layer3[12][3][5][5], kernel_bias_layer3[12];
	dense_param_t dense_param;
	int index = 0, k, r, c;

	// load weights for conv2d_layer1
	for(r = 0; r < 5; r++)
		for(c = 0; c < 5; c++)
			for(k = 0; k < 3; k++)
				kernel_weight_layer1[k][r][c] = param_arr[index++];
	for(k = 0; k < 3; k++)
		kernel_bias_layer1[k] = param_arr[index++];

	// load weights for conv2d_layer3
	for(r = 0; r < 5; r++)
		for(c = 0; c < 5; c++)
			for(int l = 0; l < 3; l++)
				for(k = 0; k < 12; k++)
					kernel_weight_layer3[k][l][r][c] = param_arr[index++];
	for(k = 0; k < 12; k++)
		kernel_bias_layer3[k] = param_arr[index++];

	// load weights for dense_layer5
	for(r = 0; r < 1920; r++)
		dense_param.weight_arr[r] = param_arr[index++];
	for(r = 0; r < 10; r++)
		dense_param.bias_arr[r] = param_arr[index++];

	// store intermediate values
	fixed_t image_data_r[28][28], layer1_output[3][24][24], layer2_output[3][12][12];
	fixed_t layer3_output[12][8][8], layer4_output[12][4][4], layer5_output[10];

	index = 0;
	for(r = 0; r < 28; r++)
		for(c = 0; c < 28; c++)
			image_data_r[r][c] = image_data[index++];

	// process
	conv2d_layer1(image_data_r, kernel_weight_layer1, kernel_bias_layer1, layer1_output);
	avgpool_layer2(layer1_output, layer2_output);
	conv2d_layer3(layer2_output, kernel_weight_layer3, kernel_bias_layer3, layer3_output);
	avgpool_layer4(layer3_output, layer4_output);
	dense_layer5(layer4_output, dense_param, layer5_output);

	// pick max
	index = 0;
	fixed_t val = layer5_output[0];
	for(int r = 1; r < 10; r++)
	{
		if(layer5_output[r] > val)
		{
			val = layer5_output[r];
			index = r;
		}
	}
	return index;
}

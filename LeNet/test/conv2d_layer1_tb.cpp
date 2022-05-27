#include "common.h"
#include <fstream>
using namespace std;

int conv2d_layer1_test()
{
	const char * const fdata = "mnist_test_0_100.txt";
	const char * const foutput = "conv2d_layer1_output.txt";
	const char * const fweights = "LeNet_weights.txt";
	ifstream fdata_ifs (fdata);
	ifstream foutput_ifs (foutput);
	ifstream fweights_ifs (fweights);

	short tmp;
	int r, c, k, i;
	fixed_t image_data_arr[100][28][28];
	fixed_t expected_output_arr[100][3][24][24];
	fixed_t output_arr[3][24][24];
	fixed_t kernel_weight_layer1[3][5][5], kernel_bias_layer1[3];


	// read kernel info
	if(fweights_ifs.is_open())
	{
		for(r = 0; r < 5; r++)
			for(c = 0; c < 5; c++)
				for(k = 0; k < 3; k++)
					fweights_ifs >> kernel_weight_layer1[k][r][c];
		for(r = 0; r < 3; r++)
			fweights_ifs >> kernel_bias_layer1[r];
		fweights_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer1]"
				<< "File [" << fweights <<"] is unable to open!" << endl;
		return 1;
	}

	// read input image [mnist dataset]
	if(fdata_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
		{
			for(r = 0; r < 28; r++)
				for(c = 0; c < 28; c++)
				{
					fdata_ifs >> tmp;
					image_data_arr[i][r][c] = tmp/255.0;	// normalization
				}
			fdata_ifs >> tmp;		// true value, not used
		}

		fdata_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer1]"
				<< "File [" << fdata <<"] is unable to open!" << endl;
		return 1;
	}

	// read output feature map
	if(foutput_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 3; k++)
				for(r = 0; r < 24; r++)
					for(c = 0; c < 24; c++)
						foutput_ifs >> expected_output_arr[i][k][r][c];

		foutput_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer1]"
				<< "File [" << foutput <<"] is unable to open!" << endl;
		return 1;
	}

	int errCount = 0, mismatch_count;
	for(i = 0; i < 100; i++)
	{
		conv2d_layer1(image_data_arr[i], kernel_weight_layer1, kernel_bias_layer1, output_arr);

		mismatch_count = 0;
		for(k = 0; k < 3; k++)
			for(r = 0; r < 24; r++)
				for(c = 0; c < 24; c++)
					if(hls::absf(expected_output_arr[i][k][r][c] - output_arr[k][r][c]) > ERROR_GAP)
						mismatch_count++;
		if(mismatch_count > 10)
		{
			errCount++;
			cout << "[conv2d_layer1] case #" << i+1 <<" mismatch_count: " << mismatch_count << endl;
		}
	}

	cout << "[conv2d_layer1] " << 100 - errCount << " test cases passed with "
					<< errCount << " cases failed." << endl;
	if(errCount > 10)
		return 1;
	return 0;
}

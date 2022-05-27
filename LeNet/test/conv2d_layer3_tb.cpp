#include "common.h"
#include <fstream>
using namespace std;

int conv2d_layer3_test()
{
	const char * const f_l2_output = "avgpool_layer2_output.txt";
	const char * const f_l3_output = "conv2d_layer3_output.txt";
	const char * const fweights = "LeNet_weights.txt";

	ifstream f_l2_ifs (f_l2_output);
	ifstream f_l3_ifs (f_l3_output);
	ifstream fweights_ifs (fweights);

	fixed_t l2_output_arr[100][3][12][12];
	fixed_t expected_output_arr[100][12][8][8];
	fixed_t output_arr[12][8][8];
	fixed_t kernel_weight_layer3[12][3][5][5], kernel_bias_layer3[12];

	fixed_t tmp;
	int k, r, c, i;

	// read kernel info
	if(fweights_ifs.is_open())
	{
		// layer1 kernel [not used]
		for(r = 0; r < 5; r++)
			for(c = 0; c < 5; c++)
				for(k = 0; k < 3; k++)
					fweights_ifs >> tmp;
		for(r = 0; r < 3; r++)
			fweights_ifs >> tmp;

		// layer3 kernel
		for(r = 0; r < 5; r++)
			for(c = 0; c < 5; c++)
				for(int l = 0; l < 3; l++)
					for(k = 0; k < 12; k++)
						fweights_ifs >> kernel_weight_layer3[k][l][r][c];
		for(r = 0; r < 12; r++)
			fweights_ifs >> kernel_bias_layer3[r];

		fweights_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer3]"
				<< "File [" << fweights <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer2 output
	if(f_l2_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 3; k++)
				for(r = 0; r < 12; r++)
					for(c = 0; c < 12; c++)
						f_l2_ifs >> l2_output_arr[i][k][r][c];

		f_l2_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer3]"
				<< "File [" << f_l2_output <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer3 output [expected value]
	if(f_l3_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 12; k++)
				for(r = 0; r < 8; r++)
					for(c = 0; c < 8; c++)
						f_l3_ifs >> expected_output_arr[i][k][r][c];

		f_l3_ifs.close();
	}
	else
	{
		cout << "[conv2d_layer3]"
				<< "File [" << f_l3_output <<"] is unable to open!" << endl;
		return 1;
	}


	int errCount = 0, mismatch_count;
	for(i = 0; i < 100; i++)
	{
		conv2d_layer3(l2_output_arr[i], kernel_weight_layer3, kernel_bias_layer3, output_arr);

		mismatch_count = 0;
		for(k = 0; k < 12; k++)
			for(r = 0; r < 8; r++)
				for(c = 0; c < 8; c++)
					if(hls::absf(expected_output_arr[i][k][r][c] - output_arr[k][r][c]) > ERROR_GAP)
						mismatch_count++;
		if(mismatch_count > 10)
		{
			errCount++;
			cout << "[conv2d_layer3] case #" << i+1 <<" mismatch_count: " << mismatch_count << endl;
		}
	}

	cout << "[conv2d_layer3] " << 100 - errCount << " test cases passed with "
					<< errCount << " cases failed." << endl;
	if(errCount > 10)
		return 1;
	return 0;
}

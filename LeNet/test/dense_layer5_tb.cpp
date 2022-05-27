#include "common.h"
#include <fstream>
using namespace std;

int dense_layer5_test()
{
	const char * const f_l4_output = "avgpool_layer4_output.txt";
	const char * const f_l5_output = "dense_layer5_output.txt";
	const char * const fweights = "LeNet_weights.txt";
	ifstream f_l4_ifs (f_l4_output);
	ifstream f_l5_ifs (f_l5_output);
	ifstream fweights_ifs (fweights);

	fixed_t l4_output_arr[100][12][4][4];
	fixed_t expected_output_arr[100][10];
	fixed_t output_arr[10];
	dense_param_t dense_param;

	int k, r, c, i;
	fixed_t tmp;

	// read dense_param info
	if(fweights_ifs.is_open())
	{
		// layer1 kernel [not used]
		for(r = 0; r < 5; r++)
			for(c = 0; c < 5; c++)
				for(k = 0; k < 3; k++)
					fweights_ifs >> tmp;
		for(r = 0; r < 3; r++)
			fweights_ifs >> tmp;

		// layer3 kernel [not used]
		for(r = 0; r < 5; r++)
			for(c = 0; c < 5; c++)
				for(int l = 0; l < 3; l++)
					for(k = 0; k < 12; k++)
						fweights_ifs >> tmp;
		for(r = 0; r < 12; r++)
			fweights_ifs >> tmp;

		// parameters of dense layer
		for(i = 0; i < 1920; i++)
			fweights_ifs >> dense_param.weight_arr[i];
		for(i = 0; i < 10; i++)
			fweights_ifs >> dense_param.bias_arr[i];

		fweights_ifs.close();
	}
	else
	{
		cout << "[dense_layer5]"
				<< "File [" << fweights <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer4 output
	if(f_l4_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 12; k++)
				for(r = 0; r < 4; r++)
					for(c = 0; c < 4; c++)
						f_l4_ifs >> l4_output_arr[i][k][r][c];

		f_l4_ifs.close();
	}
	else
	{
		cout << "[dense_layer5]"
				<< "File [" << f_l4_output <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer5 output [expected value]
	if(f_l5_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(r = 0; r < 10; r++)
				f_l5_ifs >> expected_output_arr[i][r];

		f_l5_ifs.close();
	}
	else
	{
		cout << "[dense_layer5]"
				<< "File [" << f_l5_output <<"] is unable to open!" << endl;
		return 1;
	}


	int errCount = 0, mismatch_count;
	for(i = 0; i < 100; i++)
	{
		dense_layer5(l4_output_arr[i], dense_param, output_arr);

		mismatch_count = 0;
		for(r = 0; r < 10; r++)
			if(hls::absf(expected_output_arr[i][r] - output_arr[r]) > ERROR_GAP)
					mismatch_count++;
		if(mismatch_count > 3)
		{
			errCount++;
			cout << "[dense_layer5] case #" << i+1 <<" mismatch_count: " << mismatch_count << endl;
		}
	}

	cout << "[dense_layer5] " << 100 - errCount << " test cases passed with "
					<< errCount << " cases failed." << endl;
	if(errCount > 10)
		return 1;
	return 0;
}

#include "common.h"
#include <fstream>
using namespace std;

int avgpool_layer2_test()
{
	const char * const f_l1_output = "conv2d_layer1_output.txt";
	const char * const f_l2_output = "avgpool_layer2_output.txt";
	ifstream f_l1_ifs (f_l1_output);
	ifstream f_l2_ifs (f_l2_output);

	fixed_t l1_output_arr[100][3][24][24];
	fixed_t expected_output_arr[100][3][12][12];
	fixed_t output_arr[3][12][12];

	int i, k, r, c;

	// read layer1 output
	if(f_l1_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 3; k++)
				for(r = 0; r < 24; r++)
					for(c = 0; c < 24; c++)
						f_l1_ifs >> l1_output_arr[i][k][r][c];

		f_l1_ifs.close();
	}
	else
	{
		cout << "[avgpool_layer2]"
				<< "File [" << f_l1_output <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer2 output [expected value]
	if(f_l2_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 3; k++)
				for(r = 0; r < 12; r++)
					for(c = 0; c < 12; c++)
						f_l2_ifs >> expected_output_arr[i][k][r][c];

		f_l2_ifs.close();
	}
	else
	{
		cout << "[avgpool_layer2]"
				<< "File [" << f_l2_output <<"] is unable to open!" << endl;
		return 1;
	}

	int errCount = 0, mismatch_count;
	for(i = 0; i < 100; i++)
	{
		avgpool_layer2(l1_output_arr[i], output_arr);		// DUT

		mismatch_count = 0;
		for(k = 0; k < 3; k++)
			for(r = 0; r < 12; r++)
				for(c = 0; c < 12; c++)
					if(hls::absf(expected_output_arr[i][k][r][c] - output_arr[k][r][c]) > ERROR_GAP)
						mismatch_count++;
		if(mismatch_count > 10)
		{
			errCount++;
			cout << "[avgpool_layer2] case #" << i+1 <<" mismatch_count: " << mismatch_count << endl;
		}
	}

	cout << "[avgpool_layer2] " << 100 - errCount << " test cases passed with "
					<< errCount << " cases failed." << endl;
	if(errCount > 10)
		return 1;
	return 0;
}

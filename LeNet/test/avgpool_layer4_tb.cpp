#include "common.h"
#include <fstream>
using namespace std;

int avgpool_layer4_test()
{
	const char * const f_l3_output = "conv2d_layer3_output.txt";
	const char * const f_l4_output = "avgpool_layer4_output.txt";
	ifstream f_l3_ifs (f_l3_output);
	ifstream f_l4_ifs (f_l4_output);

	fixed_t l3_output_arr[100][12][8][8];
	fixed_t expected_output_arr[100][12][4][4];
	fixed_t output_arr[12][4][4];

	int k, r, c, i;

	// read layer3 output
	if(f_l3_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 12; k++)
				for(r = 0; r < 8; r++)
					for(c = 0; c < 8; c++)
						f_l3_ifs >> l3_output_arr[i][k][r][c];

		f_l3_ifs.close();
	}
	else
	{
		cout << "[avgpool_layer4]"
				<< "File [" << f_l3_output <<"] is unable to open!" << endl;
		return 1;
	}

	// read layer4 output [expected value]
	if(f_l4_ifs.is_open())
	{
		for(i = 0; i < 100; i++)
			for(k = 0; k < 12; k++)
				for(r = 0; r < 4; r++)
					for(c = 0; c < 4; c++)
						f_l4_ifs >> expected_output_arr[i][k][r][c];

		f_l4_ifs.close();
	}
	else
	{
		cout << "[avgpool_layer4]"
				<< "File [" << f_l4_output <<"] is unable to open!" << endl;
		return 1;
	}

	int errCount = 0, mismatch_count;
	for(i = 0; i < 100; i++)
	{
		avgpool_layer4(l3_output_arr[i], output_arr);		// DUT

		mismatch_count = 0;
		for(k = 0; k < 12; k++)
			for(r = 0; r < 4; r++)
				for(c = 0; c < 4; c++)
					if(hls::absf(expected_output_arr[i][k][r][c] - output_arr[k][r][c]) > ERROR_GAP)
						mismatch_count++;
		if(mismatch_count > 10)
		{
			errCount++;
			cout << "[avgpool_layer4] case #" << i+1 <<" mismatch_count: " << mismatch_count << endl;
		}
	}

	cout << "[avgpool_layer4] " << 100 - errCount << " test cases passed with "
					<< errCount << " cases failed." << endl;
	if(errCount > 10)
		return 1;
	return 0;
}

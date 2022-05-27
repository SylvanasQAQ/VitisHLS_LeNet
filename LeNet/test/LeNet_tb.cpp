#include "common.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int LeNet_test()
{
	const char * const fdata = "mnist_test_0_1000.txt";
	const char * const fweights = "LeNet_weights.txt";
	ifstream fdata_ifs (fdata);
	ifstream fweights_ifs (fweights);

	fixed_t image_data_arr[LENET_TEST_CASES][28*28];
	short expected_val_arr[LENET_TEST_CASES], tmp, result;
	fixed_t param_arr[2944];

	// read weight info
	if(fweights_ifs.is_open())
	{
		for(int i = 0; i < 2944; i++)
			fweights_ifs >> param_arr[i];
		fweights_ifs.close();
	}
	else
	{
		cout << "[LeNet]" << "File [" << fweights <<"] is unable to open!" << endl;
		return 1;
	}

	// read image [mnist dataset]
	if(fdata_ifs.is_open())
	{
		for(int i = 0; i < LENET_TEST_CASES; i++)
		{
			for(int j = 0; j < 28*28; j++)
			{
				fdata_ifs >> tmp;
				image_data_arr[i][j] = tmp/255.0;
			}

			fdata_ifs >> expected_val_arr[i];
		}
		fdata_ifs.close();
	}
	else
	{
		cout << "[LeNet]" << "File [" << fdata <<"] is unable to open!" << endl;
		return 1;
	}


	int errCount = 0;
	for(int i = 0; i < LENET_TEST_CASES; i++)
	{
		result = LeNet(image_data_arr[i], param_arr);
		if(result != expected_val_arr[i])
			errCount++;
	}
	cout << "[LeNet] " << LENET_TEST_CASES - errCount << " test cases passed with "
				<< errCount << " cases failed." << endl;
	if(errCount > LENET_TEST_CASES/10)
		return 1;
	return 0;
}

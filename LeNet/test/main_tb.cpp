#include "common.h"
#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

int main()
{
	cout << setfill('-') << setw(50) << '-' << '\n';
	int result;
	result = conv2d_layer1_test();
	if (result != 0)
		return 1;
	result = avgpool_layer2_test();
	if (result != 0)
		return 1;
	result = conv2d_layer3_test();
	if (result != 0)
		return 1;
	result = avgpool_layer4_test();
	if (result != 0)
		return 1;
	result = dense_layer5_test();
	if (result != 0)
		return 1;
	result = LeNet_test();
	if (result != 0)
		return 1;
	cout << setfill('-') << setw(50) << '-' << '\n';
	return 0;
}

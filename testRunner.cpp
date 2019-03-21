#include "pch.h"
#include "testRunner.h"

using namespace std;

void runTests(ILPData *data) {
	cout << "A Sparse Matrix:" << endl;
	cout << data->A << endl;
	cout << "b Sparse Vector:" << endl;
	cout << data->b << endl;
	cout << "c Sparse Vector:" << endl;
	cout << data->c << endl;
}
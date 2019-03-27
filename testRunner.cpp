#include "pch.h"
#include "testRunner.h"
#include "basisUpdating/basisUpdating.h"
#include "simplex/revisedPrimalSimplex.h"

using namespace std;

void runTests(ILPData *data) {
	cout << "A Sparse Matrix:" << endl;
	cout << data->A << endl;
	cout << "b Sparse Vector:" << endl;
	cout << data->b << endl;
	cout << "c Sparse Vector:" << endl;
	cout << data->c << endl;

	/*basisUpdate(&(data->A), &(data->c), 1);
	cout << "Data after update" << endl;
	cout << data->A << endl;*/

	solveRevisedPrimalSimplex(data);
}
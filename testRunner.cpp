#include "pch.h"
#include "testRunner.h"
#include "basisUpdating/basisUpdating.h"
#include "simplex/revisedPrimalSimplex.h"
#include "matrixTools/matrixTools.h"

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

	//testing index list
	matrixIndexList *list = createIndexList();
	addIndexToList(list, 1, 1);
	addIndexToList(list, 2, 1);

	cout << "Index List Test:" << endl;
	for (matrixIndexNode *p = list->start; p != NULL; p = p->next) {
		cout << "M:" << p->index.m << ", N:" << p->index.n << endl;
	}

	freeIndexList(list);

	//testing revisedPrimalSimplexSolve
	solveRevisedPrimalSimplex(data);
}
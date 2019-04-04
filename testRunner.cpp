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

	//testing revisedPrimalSimplexSolve
	//solveRevisedPrimalSimplex(data);

	/*basisUpdate(&A, &(data->c), 1);
	cout << "Data after update" << endl;
	cout << data->A << endl;*/

	//test variables init
	SpMat A = data->A;

	//alterMatrixTest test
	/*cout << "Matrix Before:" << endl << A << endl;
	SpVec alter(2);
	alter.coeffRef(0) = 3;
	alter.coeffRef(1) = 3;
	alterMatrixColumnVector(&A, 0, 1, 1, &alter);
	cout << "Matrix After:" << endl << A << endl;*/


	//testing index list
	/*matrixIndexList *list = createIndexList();
	addIndexToList(list, 1, 1);
	addIndexToList(list, 2, 1);

	cout << "Index List Test:" << endl;
	for (matrixIndexNode *p = list->start; p != NULL; p = p->next) {
		cout << "M:" << p->index.m << ", N:" << p->index.n << endl;
	}

	freeIndexList(list);*/

	//adding zeros to column vector test
	/*addZerosToColumnVector(&A, 0, 1, 1);*/

	//vector extraction test
	/*SpVec vec;
	cout << "Vector Before: " << endl << vec << endl;
	extractVectorFromMatrix(&A, &vec, 0, 1, 1, 0);
	cout << "Vector After: " << endl << vec << endl;*/

	//Triplet extraction test
	/*TripletVector tVec;
	extractTripletsFromSparseMatrix(&A, &tVec);
	SpMat sMat(2, 2);
	cout << "Sparse Matrix Before: " << endl << sMat << endl;
	sMat.setFromTriplets(tVec.begin(), tVec.end());
	cout << "Sparse Matrix After: " << endl << sMat << endl;*/
}
#include "pch.h"
#include "testRunner.h"
#include "basisUpdating/basisUpdating.h"
#include "simplex/revisedPrimalSimplex.h"
#include "matrixTools/matrixTools.h"
#include "simplex/revisedSimplex_LU.h"

using namespace std;

void runTests(ILPData *data) {
	/*cout << "A Sparse Matrix:" << endl;
	cout << data->A << endl;
	cout << "b Sparse Vector:" << endl;
	cout << data->b << endl;
	cout << "c Sparse Vector:" << endl;
	cout << data->c << endl;*/

	//testing revisedPrimalSimplexSolve
	//solveRevisedPrimalSimplex(data);

	/*basisUpdate(&A, &(data->c), 1);
	cout << "Data after update" << endl;
	cout << data->A << endl;*/


	//revisedSimplex LU TEST
	revisedSimplexLUOut out;
	revisedSimplexLU(data, &out);

	//test variables init
	SpMat A = data->A;
	SpVec c = data->c;
	SpVec b = data->b;
	SpVec res;

	//res = A.block(0, 0, 1, 1).transpose();
	//cout << "RES: " << endl << res << endl;
	//common matrix math test
	//c.coeffRef(1) = 0;
	//removeZerosFromVector(&c);
	//res = c.cwiseProduct(b);
	//res = b - c * 5;
	//res = c.transpose() * b;
	//cout << "Result of multiplying c by b:" << endl << res << endl;

	//test pruning
	/*cout << "A before prune: " << endl << A << endl;
	A.coeffRef(0, 0) = 0;
	A.coeffRef(0, 1) = 0;
	refreshSparseMatrix(&A);
	cout << "A after prune: " << endl << A << endl;
	A.coeffRef(0, 0) = 1;
	A.makeCompressed();
	cout << "A after adding one in previous place: " << endl << A << endl;
	data->c.coeffRef(1) = 0;
	cout << "C before pruning: " << endl << data->c << endl;
	removeZerosFromVector(&data->c);
	cout << "C after pruning: " << endl << data->c << endl;*/

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
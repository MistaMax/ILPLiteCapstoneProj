#include "pch.h"
#include "factorizationRREFLP.h"
#include <cmath>
using namespace std;
void adjustVecTol(SpVec *vec, double tol);
void adjustMatTol(SpMat *mat, double tol);
//returns feasibility
int factorizationRREFLP(SpMat *A, SpVec *b, SpVec *Eq, long tol, SpVec *out, SpVec *j_b)
{
	int infeasible = 0;
	SpVec a0;
	findAllEqualities(Eq, &a0);
	//matrixIndexList *a0 = findAllEqualities(Eq);
	SpMat A_Eq;
	SpVec b_Eq;

	constructEqualityMatrix(A, &A_Eq, &a0);
	constructEqualityVector(b, &b_Eq, &a0);

	int m, n;
	m = A_Eq.rows();
	n = A_Eq.cols();

	SpMat rowIdx(2, m);
	//transpose a0 and add it to the rowIdx at index 0
	addEqualityToRowIdx(&rowIdx, &a0, m);

	int i = 0;
	int j = 0;
	//sets j_b to a vector of size 0
	SpVec j_b_tmp(0);
	*j_b = j_b_tmp;

	while (true) {
		if (i >= m || j >= n)break;
		//get the vector of the max values in each collumn (p) as well as collumn index list (k) of the Equality Max
		//check 76 implementation
		double p;
		int k;
		SpVec vectorEq;
		extractVectorFromMatrix(&A_Eq, &vectorEq, i, m-1, j, COL_VECTOR);
		getAbsMaxFromVec(&vectorEq, &p, &k);
		if (p < tol) {
			//fill A_Eq(i:m,j) with zeros
			addZerosToColumnVector(&A_Eq, i, m-1, j);
			j++;
		}
		else if (p != 0) {
			k += i - 1;//may need to remove the -1
			addValueToVectorEnd(j_b, j);//line 84, add j to j_b vector

			//i and k row vector alteration
			SpVec iRowVector, kRowVector, iColVector, kColVector;
			//line86, flip A_Eq values
			extractVectorFromMatrix(&A_Eq, &iRowVector, 0, n - 1, i, ROW_VECTOR);
			extractVectorFromMatrix(&A_Eq, &kRowVector, 0, n - 1, k, ROW_VECTOR);
			alterMatrixRowVector(&A_Eq, 0, n - 1, i, &kRowVector);
			alterMatrixRowVector(&A_Eq, 0, n - 1, k, &iRowVector);
			//line 87, flip b_Eq values
			double iVal, kVal;
			iVal = b_Eq.coeff(i);
			kVal = b_Eq.coeff(k);
			b_Eq.coeffRef(i) = kVal;
			b_Eq.coeffRef(k) = iVal;
			//line 89, flip rowIdx values at i and k
			extractVectorFromMatrix(&rowIdx, &iColVector, 0, rowIdx.rows() - 1, i, COL_VECTOR);
			extractVectorFromMatrix(&rowIdx, &kColVector, 0, rowIdx.rows() - 1, k, COL_VECTOR);
			alterMatrixColumnVector(&rowIdx, 0, rowIdx.rows() - 1, i, &kColVector);
			alterMatrixColumnVector(&rowIdx, 0, rowIdx.rows() - 1, k, &iColVector);
			//
			b_Eq.coeffRef(i) = b_Eq.coeff(i) / A_Eq.coeff(i, j);
			SpVec A_EqSubVector;
			extractVectorFromMatrix(&A_Eq, &A_EqSubVector, j, n - 1, i, ROW_VECTOR);
			A_EqSubVector = A_EqSubVector / A_Eq.coeff(i, j);
			alterMatrixRowVector(&A_Eq, j, n - 1, i, &A_EqSubVector);
			//find all non zeros in A_Eq at col j
			extractVectorFromMatrix(&A_Eq, &A_EqSubVector, 0, m - 1, j, COL_VECTOR);
			//find diff, line 95
			removeValueFromVector(&A_EqSubVector, i);
			removeZerosFromVector(&A_EqSubVector);
			//possibly alter the for loop to use innner iterators or alter the vector
			//to just contain non zero entities
			for (int t = 0; t < A_EqSubVector.rows(); t++)
			{
				if (b_Eq.coeff(i) != 0) {
					b_Eq.coeffRef(t) = b_Eq.coeff(t) - A_Eq.coeff(t, j)*b_Eq.coeff(i);
					adjustVecTol(&b_Eq, tol);
				}
				SpVec tmpVecT, tmpVecI;
				extractVectorFromMatrix(&A_Eq, &tmpVecT, j, n - 1, t, ROW_VECTOR);
				extractVectorFromMatrix(&A_Eq, &tmpVecI, j, n - 1, i, ROW_VECTOR);
				tmpVecT = tmpVecT - A_Eq.coeff(t, j)*tmpVecI;
				alterMatrixRowVector(&A_Eq, j, n - 1, t, &tmpVecT);
				adjustMatTol(&A_Eq, tol);
			}
			i++;
			j++;
		}
	}
	//check for redundant and infeasible constraints, line 119
	i = 0;
	return infeasible;
}

void getAbsMaxFromVec(SpVec *vec, double *maxVal, int *maxIdx) {
	int m = vec->rows();
	*maxVal = abs(vec->coeff(0));
	*maxIdx = 0;
	for (int i = 1; i < m; i++) {
		if (*maxVal < abs(vec->coeff(i))) {
			*maxVal = abs(vec->coeff(i));
			*maxIdx = i;
		}
	}
}

void addEqualityToRowIdx(SpMat *rowIdx, SpVec *a0, int m) {
	for (int i = 0; i < m; i++) {
		rowIdx->coeffRef(0, i) = a0->coeff(i);
	}
}

void removeValueFromVector(SpVec *vec, double value) {
	int m = vec->rows();
	for (int i = 0; i < m; i++) {
		if (value == vec->coeff(i))
			vec->coeffRef(i) = 0;
	}
}

void adjustVecTol(SpVec *vec, double tol)
{
	int m = vec->rows();
	for (int i = 0; i < m; i++) {
		if (abs(vec->coeff(i)) <= tol)
			vec->coeffRef(i) = 0;
	}
}

void adjustMatTol(SpMat *mat, double tol)
{
	int m = mat->rows(), n = mat->cols();
	for (int k = 0; k < mat->outerSize(); ++k) {
		for (SparseMatrix<double>::InnerIterator it(*mat, k); it; ++it) {
			if (abs(it.value()) > tol)
				mat->coeffRef(it.row(), it.col()) = 0;
		}
	}
}
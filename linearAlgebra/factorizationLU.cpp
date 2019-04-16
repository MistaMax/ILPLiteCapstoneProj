
#include "pch.h"
#include "factorizationLU.h"
void getAbsMaxFromVector(SpVec *vec, double *maxVal, int *maxIdx);
//check for bound restrictions
void factorizationLU(SpMat *A, SpMat *L, SpMat *U, SpMat *P)
{
	int s;
	//determine focus
	if (A->rows() >= A->cols()) {
		s = A->rows();
	}
	else
		s = A->cols();

	*U = *A;
	L->resize(s, s);

	SpVec PV(s);//transpose this later
	for (int i = 1; i < s; i++) {
		PV.coeffRef(i) = i;
	}
	//may need to remove -1 from j-1 occurences
	for (int i = 0; i < s; i++) {
		//pivot voting (max value in this column first
		double maxVal, t;
		int maxIdx;
		SpVec tmp;
		int j = i;

		extractVectorFromMatrix(U, &tmp, j, s - 1, j, COL_VECTOR);
		getAbsMaxFromVector(&tmp, &maxVal, &maxIdx);
		maxIdx = maxIdx + j;//CHECK IF YOU ACTUALLY NEED -1

		//pivot PV
		t = PV.coeff(j);
		PV.coeffRef(j) = PV.coeff(maxIdx);
		PV.coeffRef(maxIdx) = t;

		//pivot L
		SpVec LPrev, LNext;
		extractVectorFromMatrix(L, &LPrev, 0, j - 1, j, ROW_VECTOR);//may need to be -2
		extractVectorFromMatrix(L, &LNext, 0, j - 1, maxIdx, ROW_VECTOR);
		alterMatrixRowVector(L, 0, j - 1, j, &LNext);
		alterMatrixRowVector(L, 0, j - 1, maxIdx, &LPrev);
		//pivot U, CHECK THIS
		SpVec UPrev, UNext;
		extractVectorFromMatrix(U, &UPrev, j, U->cols() - 1, j, ROW_VECTOR);
		extractVectorFromMatrix(U, &UNext, j, U->cols() - 1, maxIdx, ROW_VECTOR);
		alterMatrixRowVector(U, j, U->cols() - 1, j, &UNext);
		alterMatrixRowVector(U, j, U->cols() - 1, maxIdx, &UPrev);
		//LU CHECK THIS
		L->coeffRef(j, j) = 1;
		for (int z = (1 + j); z < U->rows(); z++) {
			double c = U->coeff(z, j) / U->coeff(j, j);
			SpVec upperZ, upperJ;
			extractVectorFromMatrix(U, &upperZ, j, s - 1, z, ROW_VECTOR);
			extractVectorFromMatrix(U, &upperJ, j, s - 1, j, ROW_VECTOR);
			upperZ = upperZ - upperJ * c;
			alterMatrixRowVector(U, j, s - 1, z, &upperZ);
			L->coeffRef(z, j) = c;
		}
	}

	P->resize(s, s);
	//check line 62 for P implementation
	P->setIdentity();
}


void getAbsMaxFromVector(SpVec *vec, double *maxVal, int *maxIdx) {
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
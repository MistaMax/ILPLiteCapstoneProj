
#include "pch.h"
#include "factorizationLU.h"
void getAbsMaxFromVector(SpVec *vec, double *maxVal, int *maxIdx);
//check for bound restrictions
void factorizationLU(SpMat *A, SpMat *L, SpMat *U, SpMat *P)
{
	int s;

	if (A->rows() >= A->cols())
		s = A->rows();
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
		maxIdx = maxIdx + (j - 1);//CHECK IF YOU ACTUALLY NEED -1

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
		//pivot U
		//check line 50 of factorizationLU for U pivot context

		//LU
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

/*int factorization(MatrixXd A, MatrixXd* L, MatrixXd* U, MatrixXd* P) {
	int s = A.innerSize();
	*U = A;
	MatrixXd mat(s, s);
	*L = mat;
	Index ind;
	//Index t;
	MatrixXd t;
	MatrixXd PV = mat.transpose();
	for (int j = 0; j < s; j++) {
		U->col(j).cwiseAbs.maxCoeff(&ind);
		ind = ind + (j - 1);

		t = PV.col(j);
		PV.col(j) = PV.col(ind);
		PV.col(ind) = t;

		t = L->block(j, 1, j, j - 1);
		L->block(j, 1, L->cols(), j - 1) = L->block(ind, 1, L->cols(), j - 1);
		L->block(ind, 1, L->cols(), j - 1) = t;

		// Apr 8th: may be slightly wrong, adjustment needed
		t = U->block(j, j, U->cols() - j, 1);
		U->block(j, j, U->cols() - j, 1) = U->block(ind, j, U->cols() - j, 1);
		U->block(ind, j, U->cols() - j, 1) = t;

		// LU

		(*L)(j,j) = 1;
		//Could be U->outerSize
		for (int i = j + 1; i < U->cols(); i++) {

		}
		

		

		
	}
}*/
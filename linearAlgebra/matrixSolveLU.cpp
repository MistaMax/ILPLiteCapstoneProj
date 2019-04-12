#include "pch.h"
#include "matrixSolveLU.h"

void matrixSolveLU(SpMat *A, SpVec *b, SpVec *X, SpMat *P)
{
	int numRows, numCols;
	numRows = A->rows();
	numCols = A->cols();

	SpMat L, U;
	factorizationLU(A, &L, &U, P);
	SpVec Y(numRows);
	X->resize(numRows);
	SpVec rhs;
	rhs = (*P) * (*b);

	for (int i = 0; i < numCols; i++) {
		Y.coeffRef(i) = rhs.coeff(i);
		SpVec tmp;
		extractVectorFromMatrix(&L, &tmp, 0, L.rows()-1, i, COL_VECTOR);
		rhs = rhs - (Y.coeff(i)*tmp);
	}

	for (int i=numCols-1;i>=0; i--) {
		X->coeffRef(i) = Y.coeff(i) / U.coeff(i, i);
		SpVec tmp;
		extractVectorFromMatrix(&U, &tmp, 0, U.rows() - 1, i, COL_VECTOR);
		Y = Y - (X->coeff(i)*tmp);
	}
}

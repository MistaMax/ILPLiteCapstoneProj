
#include "pch.h"
#include "factorizationLU.h"



int factorization(MatrixXd A, MatrixXd* L, MatrixXd* U, MatrixXd* P) {
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
}
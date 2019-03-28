#include "pch.h"
#include "factorizationRREF_LP.h"
//returns feasibility
int factorizationRREF_LP(SpMat *A, SpVec *b, SpVec *Eq, int tol, matrixIndexList *out, SpMat *j_b)
{
	int infeasible = 0;
	SpVec a0;
	findAllEqualities(Eq, &a0);
	//matrixIndexList *a0 = findAllEqualities(Eq);
	SpMat A_Eq;
	SpVec b_Eq;

	constructEqualityMatrix(A,&A_Eq,&a0);
	constructEqualityVector(b, &b_Eq,&a0);

	int m, n;
	m = A_Eq.rows();
	n = A_Eq.cols();

	SpMat rowIdx(2, m);
	//transpose a0 and add it to the rowIdx at index 0
	addEqualityToRowIdx(&rowIdx, &a0, m);

	int i = 0;
	int j = 0;
	SpMat j_b(m, m);

	while (true) {
		if (i >= m || j >= n)break;

	}
	return infeasible;
}

void addEqualityToRowIdx(SpMat *rowIdx, SpVec *a0, int m) {
	for (int i = 0; i < m; i++) {
		rowIdx->coeffRef(0, i) = a0->coeff(i);
	}
}

#include "pch.h"
#include "revisedSimplex_LU.h"

using namespace std;

void revisedSimplexLU(ILPData *data, revisedSimplexLUOut *output)
{
	SpMat A = data->A;
	SpVec c = data->c;
	SpVec b = data->b;
	SpVec bv = data->bv;
	
	SpVec x(A.rows());
	double fVal = 0;
	int iter = 0;
	//saving the size
	int m, n;
	m = A.rows();
	n = A.cols();

	if (bv.rows() == 0) {
		//do stuff here 96
		SpMat A_id(m, n);
		A_id.setIdentity();
		A.conservativeResize(m + m, n);

		for (int i = m, j = 0; i < 2 * m; i++, j++) {
			SpVec tmp;
			extractVectorFromMatrix(&A_id, &tmp, 0, n - 1, j, ROW_VECTOR);
			alterMatrixRowVector(&A, 0, n - 1, i, &tmp);
		}

		c.conservativeResize(m + m);

		bv.resize(m);

		for (int i = 0; i < m; i++) {
			bv.coeffRef(i) = m + i;
		}
	}

	//STEP 1: INITIALIZATION

	int numRows = b.rows();
	int numVars = c.rows();
	//tolerance gap, line 115
	double epsilon = 1e-5;

	SpVec nb;//use .transpose() to make a row vector as apposed to a collumn vector
	SpMat A_nb, A_bv;
	SpVec c_nb, c_bv;
	int newM=A.rows();
	//indecies of the nonbasic variables
	nb.resize(m);
	
	for (int i = 0; i < m; i++) {
		nb.coeffRef(i) = i;
	}
	//number nonbasic variables
	int numNonBasicVars = nb.rows();
	int numBasicVars = bv.rows();
	//basis matrix (123)
	A_bv.resize(newM, numBasicVars);
	for (int i = 0; i < numBasicVars; i++) {
		SpVec tmp;
		extractVectorFromMatrix(&A, &tmp, 0, newM - 1, bv.coeff(i), COL_VECTOR);
		alterMatrixColumnVector(&A_bv, 0, newM - 1, i, &tmp);
	}
	//non-basic matrix
	A_nb.resize(newM, numNonBasicVars);
	for (int i = 0; i < numNonBasicVars; i++) {
		SpVec tmp;
		extractVectorFromMatrix(&A, &tmp, 0, newM - 1, nb.coeff(i), COL_VECTOR);
		alterMatrixColumnVector(&A_nb, 0, newM - 1, i, &tmp);
	}


	output->x = x;
	output->fVal = fVal;
	output->iter = iter;
}
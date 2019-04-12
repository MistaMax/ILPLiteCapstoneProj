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
	genSubMatrixFromIndecies(&A, &A_bv, &bv, ROW_VECTOR);

	//non-basic matrix
	genSubMatrixFromIndecies(&A, &A_nb, &nb, ROW_VECTOR);

	//basic and non-basic vector [c]
	genSubVectorFromIndecies(&c, &c_nb, &nb);
	genSubVectorFromIndecies(&c, &c_bv, &bv);

	//initialized variables
	cout << ">>>INITIALIZED DATA<<<" << endl;
	cout << "A: " << endl << A << endl;
	cout << "A_bv: " << endl << A_bv << endl;
	cout << "A_nb: " << endl << A_nb << endl;
	cout << "c: " << endl << c << endl;
	cout << "c_nb: " << endl << c_nb << endl;
	cout << "c_bv: " << endl << c_bv << endl;
	cout << ">>>END INITIALIZED DATA<<<" << endl;

	SpVec b_bar;
	SpMat P;
	matrixSolveLU(&A_bv, &b, &b_bar, &P);

	fVal = c_bv.dot(b_bar);
	cout << "FVAL: " << endl << fVal << endl;

	output->x = x;
	output->fVal = fVal;
	output->iter = iter;
}
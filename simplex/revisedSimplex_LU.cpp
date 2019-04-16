#include "pch.h"
#include "revisedSimplex_LU.h"

using namespace std;

double findMinInVector(SpVec *vec);
double findMinInMatrix(SpMat *mat, int *index);

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
		A.conservativeResize(m, n+n);

		for (int i = n, j = 0; i < 2 * n; i++, j++) {
			SpVec tmp;
			extractVectorFromMatrix(&A_id, &tmp, 0, m - 1, j, COL_VECTOR);
			alterMatrixColumnVector(&A, 0, m - 1, i, &tmp);
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
	genSubMatrixFromIndecies(&A, &A_bv, &bv, COL_VECTOR);

	//non-basic matrix
	genSubMatrixFromIndecies(&A, &A_nb, &nb, COL_VECTOR);

	//basic and non-basic vector [c]
	genSubVectorFromIndecies(&c, &c_nb, &nb);
	genSubVectorFromIndecies(&c, &c_bv, &bv);

	//initialized variables
	/*cout << ">>>INITIALIZED DATA<<<" << endl;
	cout << "A: " << endl << A << endl;
	cout << "A_bv: " << endl << A_bv << endl;
	cout << "A_nb: " << endl << A_nb << endl;
	cout << "c: " << endl << c << endl;
	cout << "c_nb: " << endl << c_nb << endl;
	cout << "c_bv: " << endl << c_bv << endl;
	cout << ">>>END INITIALIZED DATA<<<" << endl;
	*/
	SpVec b_bar;
	SpMat P;

	matrixSolveLU(&A_bv, &b, &b_bar, &P);
	fVal = c_bv.dot(b_bar);
	/*
	cout << "P: " << endl << P << endl;
	cout << "B_Bar: " << endl << b_bar << endl;
	cout << "A_bv:" << endl << A_bv << endl;
	cout << "FVAL: " << endl << fVal << endl;
	*/
	int minRatioIdx = 1, negRedCostIdx = 0;
	iter = 0;
	double negRedCost = -1;
	while (true) {
		if (negRedCost >= 0 || iter >= MAX_ITER)break;
		iter++;
		SpMat transA_bv = A_bv.transpose();
		SpVec u;
		//LU DECOMPOSITION SOLVE
		matrixSolveLU(&transA_bv, &c_bv, &u, &P);
		A_bv = transA_bv.transpose();
		SpMat w_nb;

		w_nb = c_nb.transpose() - u.transpose()*A_nb;
		negRedCost = 0;
		negRedCostIdx = 0;
		int negRedIdxTmp;
		if (findMinInMatrix(&w_nb, &negRedIdxTmp) < -1*epsilon) {
			negRedCost = findMinInMatrix(&w_nb, &negRedCostIdx);
		}
		else
			negRedCostIdx = 0;

		if (negRedCost < 0) {
			//Step 3: minimum ratio test
			SpVec a_bar, negRedCostA_nb;
			extractVectorFromMatrix(&A_nb, &negRedCostA_nb, 0, A_nb.rows() - 1, negRedCostIdx, COL_VECTOR);
			matrixSolveLU(&A_bv, &negRedCostA_nb, &a_bar, &P);
			double minRatioVal = INFINITY;
			//minRatioIdx = 0;
			for (int i = 0; i < numRows; i++) {
				if (a_bar.coeff(i) > epsilon) {
					if (b_bar.coeff(i) / a_bar.coeff(i) < minRatioVal) {
						minRatioVal = b_bar.coeff(i) / a_bar.coeff(i);
						minRatioIdx = i;
					}
				}
			}
			//Step 4: Pivot and update
			b_bar = b_bar - minRatioVal * a_bar;
			b_bar.coeffRef(minRatioIdx) = minRatioVal;

			//Step 5: UPDATE BASIS
			double tmpIdx = bv.coeff(minRatioIdx);
			bv.coeffRef(minRatioIdx) = nb.coeff(negRedCostIdx);
			nb.coeffRef(negRedCostIdx) = tmpIdx;

			//update Basic and Non-Basic matricies
			genSubMatrixFromIndecies(&A, &A_bv, &bv, COL_VECTOR);

			//non-basic matrix
			genSubMatrixFromIndecies(&A, &A_nb, &nb, COL_VECTOR);

			//basic and non-basic vector [c]
			genSubVectorFromIndecies(&c, &c_nb, &nb);
			genSubVectorFromIndecies(&c, &c_bv, &bv);
		}//negRedCost<0

		//get the solution
		x.resize(numVars);
		for (int i = 0; i < numRows; i++) {
			x.coeffRef(bv.coeff(i)) = b_bar.coeff(i);
		}

		//get the objective value
		fVal = c_bv.dot(b_bar);
		cout << "Iter: " << iter << ", Fval: " << fVal << endl;
	}
	cout << "x" << endl << x << endl;
	cout << "fVal" << endl << fVal << endl;
	output->x = x;
	output->fVal = fVal;
	output->iter = iter;
}

double findMinInVector(SpVec *vec) {
	double min = vec->coeff(0);
	for (int i = 1; i < vec->rows(); i++) {
		if (vec->coeff(i) < min)
			min = vec->coeff(i);
	}
	return min;
}

double findMinInMatrix(SpMat *mat, int *index) {
	int m, n;
	double min = mat->coeff(0,0);
	*index = 0;
	m = mat->rows();
	n = mat->cols();

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat->coeff(j, i) < min) {
				min = mat->coeff(j, i);
				*index = i;
			}
		}
	}
	return min;
}
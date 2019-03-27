#include "pch.h"
#include "revisedPrimalSimplex.h"
#include "../matrixTools/matrixTools.h"
#include "../linearAlgebra/linearAlgebra.h"

Output solveRevisedPrimalSimplex(ILPData *data) {
	Logger::getInstance().logInfo("\n\n>>>> Revised Primal Simplex <<<<\n");
	//Initializing variables
	SpVec x_star;
	double fVal = 0;
	short exitFlag = 0;
	int iter = 0;
	int flag = 0;

	//output structure check 78
	Output output;
	//output.x;
	output.fVal = 0;
	output.exitFlag = 0;
	output.iter = 0;
	//output.bv;
	//initialize size variables
	int m, n, m2, n2, m3, n3, m4, n4;
	//get the sizes
	m = data->A.rows();
	n = data->A.cols();
	m2 = data->c.rows();
	n2 = data->c.cols();
	m3 = data->A_eq.rows();
	n3 = data->A_eq.cols();
	m4 = data->b.rows();
	n4 = data->b.cols();

	SpMat A = data->A;
	SpVec c = data->c;
	SpVec b = data->b;
	SpMat A_eq = data->A_eq;
	double c0 = data->c0;

	if (A_eq.nonZeros() == 0)
		flag = 1;
	else
		flag = 0;
	//add opts.MinMaxLP here, chech 122 in revisedPrimalSimplex.m
	if (flag == 1)//all constraints are equalities
	{
		//run factorization
		//check line # 129
		int out = 0;
		SpMat j_b;
		int infeasible = factorizationRREF_LP(&A, &b, &A_eq, 1e-10, &out, &j_b);

		if (infeasible == 1) {
			output.exitFlag = 1;
			return output;
		}

		//remove redundant constraints here
	}
	else//some or all constraints are inequalities
	{
		//add slack variables
		int slackVars = A_eq.nonZeros();
		//int slackVars = 2;
		//for all elements at index m2+1 to m2+slackVars
		addSlackToVector(&c, m2, slackVars);
		addSlackToMatrix(&A, m, n, 0, slackVars);
		int col_inc = 1;
		//156 in matlab code
		for (int i = 0; i < m3; i++) {
			//'greater than or equal to' inequality constraint
			if (A_eq.coeff(i, 0) == 1) {
				A.coeffRef(i, n + col_inc) = -1;
				col_inc += 1;
			}
			//'less than or equal to' inequality constraint
			else if (A_eq.coeff(i, 0) == -1) {
				A.coeffRef(i, n + col_inc) = 1;
				col_inc += 1;
			}
			//unrecognized type of constraint
			else {
				output.exitFlag = -1;
				return output;
			}
		}

		//select an initial invertible basis using factorizationRREF_LP function
		int out = 0;//not actually an int, contains indecies for all the redundant constraints
		SpMat j_b;
		int infeasible = factorizationRREF_LP(&A, &b, &A_eq, 1e-10, &out, &j_b);

		if (infeasible == 1) {
			output.exitFlag = 1;
			return output;
		}


	}


	return output;
}
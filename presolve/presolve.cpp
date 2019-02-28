#include "pch.h"
#include "presolve.h"
#include "fullRank.h"
#include "eliminateDualSingletonInequalityConstraints.h"
#include "eliminateImpliedBoundsonRows.h"
#include "eliminateImpliedFreeSingletonColumns.h"
#include "eliminateKtonEqualityConstraints.h"
#include "eliminateRedundantColumns.h"
#include "eliminateRedundantRows.h"
#include "eliminateSingletonEqualityConstraints.h"
#include "eliminateSingletonInequalityConstraints.h"
#include "eliminateZeroColumns.h"
#include "eliminateZeroRows.h"

using namespace std;
//returns 1 if infeasible, returns 2 if unbounded
int presolve(ILPData *data)
{
	//get the size of A
	int m = data->A.rows();
	int n = data->A.cols();
	//initialize the temporary variables
	double c0;
	MatrixXd A(m,n);
	VectorXd b(m), c(n), A_eq(m);
	//clone the Matrix data
	A = data->A;
	b = data->b;
	c = data->c;
	A_eq = data->A_eq;
	c0 = data->c0;
	//save the initial size of A
	int m_init = m;
	int n_init = n;
	//factors for determining if simplex is possible
	int infeasible = 0;
	int unbounded = 0;

	int m_prev = 0;
	int n_prev = 0;

	while (m_prev < m) //figure out how to determine ~= in c++
	{
		infeasible = eliminateZeroRows(&A, &b, &A_eq);
		if (infeasible == 1)
			return 1;

		unbounded = eliminateZeroColumns(&A, &c, &A_eq);
		if (unbounded == 1)
			return 2;

		infeasible = eliminateKtonEqualityConstraints(&A, &c, &b, &A_eq, &c0);
		if (infeasible == 1)
			return 1;

		m_prev = m;
	}

	return 0;
}
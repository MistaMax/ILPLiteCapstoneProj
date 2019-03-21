#pragma once

#include <Eigen/Sparse>
#include <cstdint>
#include <string>

using namespace Eigen;
// values :
//   data : data structure
//               -data.A : m - by - n constraint matrix
//               -data.b : m - by - 1 right - hand side vector
//               -data.c : m - by - 1 cost vector.
//               -data.Eq : m - by - 1 vector of the type of the constraints
// (-1) = "<=" constraint, (0) = "=" constraint, (1) ">=" constraint
//               -data.c0 : scalar constant term of the objective function
// (default value = 0)
// -data.lb : n - by - 1 lower - bound vector
//               -data.ub : n - by - 1 upper - bound vector
//               -data.x0 : m - by - 1 initial solution vector
//               -data.bv : n - by - 1 basic variables vector
//               -data.intCon : n - by - 1 logical vector of integer constraints
typedef struct ILPData {
	Matrix<double, Dynamic, Dynamic, 0, 10, 10> A;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> b;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> c;
	Matrix<double, Dynamic, Dynamic, 0, 10, 10> A_eq;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> b_eq;
	double c0;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> lb;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> ub;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> x0;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> bv;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> intCon;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> row_multi;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> col_multi;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> row_multieq;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> col_multieq;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> BasicList;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> NonBasicList;
	Matrix<double, Dynamic, Dynamic, 0, 10, 10> BasisInv;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> S_n;
	Matrix<double, Dynamic, Dynamic, 0, 10, 1> x_bar;
	int pivot;
	int iter;
}ILPData;
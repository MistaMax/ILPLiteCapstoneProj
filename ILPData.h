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

typedef SparseMatrix<double> SpMat;
typedef SparseVector<double> SpVec;
typedef Triplet<double> Trip;

typedef Matrix<double, Dynamic, Dynamic, 0, 10, 10> DenMat;
typedef Matrix<double, Dynamic, Dynamic, 0, 10, 1> DenVec;
//Currently using dense matricies for storage, these typedefs will allow us to change the storage to sparse matricies
//when I figure out how to declare a dynamic sparse matrix at compile time
//dense matrix
/*
typedef Matrix<double, Dynamic, Dynamic, 0, 10, 10> Mat;
typedef Matrix<double, Dynamic, Dynamic, 0, 10, 1> Vec;
*/
//just testing the datastructure out
typedef struct ILPData {
	SpMat A;
	SpVec b;
	SpVec c;
	SpMat A_eq;
	SpVec b_eq;
	double c0;
	SpVec lb;
	SpVec ub;
	SpVec x0;
	SpVec bv;
	SpVec intCon;
	SpVec row_multi;
	SpVec col_multi;
	SpVec row_multieq;
	SpVec col_multieq;
	SpVec BasicList;
	SpVec NonBasicList;
	SpMat BasisInv;
	SpVec S_n;
	SpVec x_bar;
	int pivot;
	int iter;
}ILPData;

typedef struct ILPDenseData {
	DenMat A;
	DenVec b;
	DenVec c;
	DenMat A_eq;
	DenVec b_eq;
	double c0;
	DenVec lb;
	DenVec ub;
	DenVec x0;
	DenVec bv;
	DenVec intCon;
	DenVec row_multi;
	DenVec col_multi;
	DenVec row_multieq;
	DenVec col_multieq;
	DenVec BasicList;
	DenVec NonBasicList;
	DenMat BasisInv;
	DenVec S_n;
	DenVec x_bar;
	int pivot;
	int iter;
}ILPDenseData;
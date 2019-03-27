#include "pch.h"
#include "matrixTools.h"

using namespace std;
SpMat genIdentityMatrix(int m, int n) {
	SpMat sparseIdentity = genDenseIdentityMatrix(m, n).sparseView();
	return sparseIdentity;
}

DenMat genDenseIdentityMatrix(int m, int n) {
	MatrixXd identity(m, n);
	identity = MatrixXd::Identity(m, n);
	return identity;
}

void addSlackToMatrix(SpMat *mat, int m, int n, int slackM, int slackN) {
	mat->conservativeResize(m + slackM, n + slackN);
	//add more code to initialize the zeros
}

void addSlackToVector(SpVec *vec, int m, int slack) {
	vec->conservativeResize(m + slack);
}
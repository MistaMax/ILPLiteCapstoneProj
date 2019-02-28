#pragma once
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;
int eliminateKtonEqualityConstraints(MatrixXd *A, VectorXd*c, VectorXd *b, VectorXd *A_eq, double *c0);
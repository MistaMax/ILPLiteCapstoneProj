#pragma once
#include <Eigen/Dense>
#include <string>
#include <iostream>
using namespace Eigen;
using namespace std;
int eliminateDualSingletonInequalityConstraints(MatrixXd *A, VectorXd *c, VectorXd *b, VectorXd *A_eq);
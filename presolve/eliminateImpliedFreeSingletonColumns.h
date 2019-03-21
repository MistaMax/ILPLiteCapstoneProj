#pragma once
#include <Eigen/Dense>
#include <string>
#include <iostream>

using namespace Eigen;
using namespace std;

void eliminateImpliedFreeSingletonColumns(MatrixXd *A, VectorXd *c, VectorXd *b, VectorXd *A_eq, double c0);
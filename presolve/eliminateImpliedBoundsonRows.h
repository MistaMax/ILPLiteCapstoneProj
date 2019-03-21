#pragma once
#include <Eigen/Dense>
#include <string>
#include <iostream>

using namespace Eigen;
using namespace std;

void eliminateImpliedBoundsonRows(MatrixXd *A, VectorXd *b, VectorXd *A_eq);
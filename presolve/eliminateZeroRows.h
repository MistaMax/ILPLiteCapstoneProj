#pragma once
#include "../dense.h"
#include <Eigen/Dense>
#include <string>
using namespace Eigen;
using namespace std;

int eliminateZeroRows(MatrixXd *A, VectorXd *b, VectorXd *A_eq);
#pragma once
#include <Eigen/Dense>
#include <string>
#include <iostream>

using namespace Eigen;
using namespace std;

void fullRank(MatrixXd *A, MatrixXd *A_temp, VectorXd *b, VectorXd *A_eq);
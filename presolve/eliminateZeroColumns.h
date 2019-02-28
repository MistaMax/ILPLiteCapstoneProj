#pragma once
#include <Eigen/Dense>
#include <string>
using namespace Eigen;
using namespace std;

int eliminateZeroColumns(MatrixXd *A, VectorXd *c, VectorXd *A_eq);
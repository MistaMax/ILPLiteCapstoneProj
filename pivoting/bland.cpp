/*
 * bland.cpp based on the ILP-Lite implementation
 *
 *  Created on: Feb 19, 2019
 *      Author: Devin Nguyen
 */


#include <iostream>
#include <Eigen/Sparse>
#include <vector>

using namespace std;
using namespace Eigen;

Index bland(SparseVector<double> S_n, SparseVector<double> NonBasicList){
	//Check for all non-zero values
	Index nonZeros = S_n.nonZeros();
	Index rowIdx;
	//Find the smallest value
	double value = VectorXd::Map(NonBasicList.valuePtr(),nonZeros).minCoeff(&rowIdx);
	//Return the Eigen::Index of the entering variable
	return NonBasicList.innerIndexPtr()[rowIdx];
}

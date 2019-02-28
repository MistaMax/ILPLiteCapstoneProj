/*
 * dantzig.cpp
 *
 *  Created on: Feb 28, 2019
 *      Author: Devin Nguyen
 */

#include <vector>
#include <Eigen>
int dantzig(Eigen::VectorXd S_n){
	int idx = 0;
	S_n.minCoeff(&idx);
	//int first, second = std::min_element(S_n.be, std::end(S_n))
	return idx;
}



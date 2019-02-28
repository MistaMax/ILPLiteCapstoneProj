/*
 * bland.cpp based on the ILP-Lite implementation
 *
 *  Created on: Feb 19, 2019
 *      Author: Devin Nguyen
 */


#include <iostream>
#include <Eigen/Dense>
#include <vector>



int bland(Eigen::VectorXd S_n, Eigen::VectorXi NonBasicList){
	std::vector<Eigen::Index> idxs;
	//Eigen::VectorXi::Index idxs;
	for(Eigen::Index i = 0; i < S_n.size(); i++){
		if(S_n(i) < 0){
			//Add indices to list
			idxs.push_back(i);
		}
	}
	// Unsure if this next line will work
	int first, second = std::min_element(std::begin(idxs), std::end(idxs));

	return idxs(second);
}

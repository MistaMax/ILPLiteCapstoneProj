#include "pch.h"
#include <vector>
#include "ScalingMisc.h"
#include <Eigen/Dense>
#include "../ILPData.h"

using namespace std;
using namespace Eigen;

void arithmeticMean(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_sum(m);
	RowVectorXd col_sum(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		//ind = find_NonZero(data.A.row(i));
		ind.clear();
		for (int j = 0; j < data.A.cols(); j++)
		{
			if (data.A(i,j) != 0)
				ind.push_back(j);
		}
		if(!ind.empty()) 
		{
			row_sum(i) = sum_abs(data.A.row(i), &ind);
			data.row_multi(i) = ind.size() / row_sum(i);
			data.A.row(i) = data.A.row(i) * data.row_multi(i);
			data.b(i) = data.b(i) * data.row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		//ind = find_NonZero(data.A.col(i));
		for (int j = 0; j < data.A.cols(); j++)
		{
			if (data.A(j, i) != 0)
				ind.push_back(j);
		}
		if (!ind.empty())
		{
			col_sum(i) = sum_abs(data.A.col(i), &ind);
			data.col_multi(i) = ind.size() / col_sum(i);
			data.A.col(i) = data.A.col(i) * data.col_multi(i);
			data.c(i) = data.c(i) * data.col_multi(i);
		}
	}
}


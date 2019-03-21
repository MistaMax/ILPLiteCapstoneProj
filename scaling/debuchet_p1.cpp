#include "pch.h"
#include <vector>
#include "ScalingMisc.h"
#include <Eigen/Dense>
#include "../ILPData.h"

using namespace std;

void debuchet_p1(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_sum(m);
	RowVectorXd row_inv_sum(m);

	RowVectorXd col_sum(n);
	RowVectorXd col_inv_sum(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		ind.clear();
		find_NonZero(data.A.row(i),&ind);
		if (!ind.empty())
		{
			row_sum(i) = sum_abs(data.A.row(i), &ind);
			row_inv_sum(i) = sum_inv_abs(data.A.row(i), &ind);
			data.row_multi(i) = pow(row_inv_sum(i) / row_sum(i),.5);
			data.A.row(i) = data.A.row(i) * data.row_multi(i);
			data.b(i) = data.b(i) * data.row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		ind.clear();
		find_NonZero(data.A.col(i),&ind);
		if (!ind.empty())
		{
			col_sum(i) = sum_abs(data.A.col(i), &ind);
			col_inv_sum(i) = sum_inv_abs(data.A.col(i), &ind);
			data.col_multi(i) = pow(col_inv_sum(i) / col_sum(i), .5);
			data.A.col(i) = data.A.col(i) * data.col_multi(i);
			data.c(i) = data.c(i) * data.col_multi(i);
		}
	}
}
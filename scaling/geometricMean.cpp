#include <vector>
#include "ScalingMisc.h"
#include <Eigen/Dense>
#include "ILPData.h"

using namespace std;

void geometricMean(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_pow(m);
	RowVectorXd row_inv_pow(m);

	RowVectorXd col_pow(n);
	RowVectorXd col_inv_pow(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		ind.clear();
		find_NonZero(data.A.row(i), &ind);
		if (!ind.empty())
		{
			row_pow(i) = sum_sqrd(data.A.row(i), &ind);
			row_inv_pow(i) = sum_inv_sqrd(data.A.row(i), &ind);
			data.row_multi(i) = pow(row_inv_pow(i) / row_pow(i), .25);
			data.A.row(i) = data.A.row(i) * data.row_multi(i);
			data.b(i) = data.b(i) * data.row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		ind.clear();
		find_NonZero(data.A.col(i), &ind);
		if (!ind.empty())
		{
			col_pow(i) = sum_sqrd(data.A.col(i), &ind);
			col_inv_pow(i) = sum_inv_sqrd(data.A.col(i), &ind);
			data.col_multi(i) = pow(col_inv_pow(i) / col_pow(i), .25);
			data.A.col(i) = data.A.col(i) * data.col_multi(i);
			data.c(i) = data.c(i) * data.col_multi(i);
		}
	}
}
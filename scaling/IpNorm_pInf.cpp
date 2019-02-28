#include <vector>
#include "ScalingMisc.h"
#include <Eigen/Dense>
#include "ILPData.h"

using namespace std;

void IpNorm_pInf(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_max(m);
	RowVectorXd row_min(m);

	RowVectorXd col_max(n);
	RowVectorXd col_min(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		find_NonZero(data.A.row(i),&ind);
		if (!ind.empty())
		{
			row_max(i) = max_abs(data.A.row(i), &ind);
			row_min(i) = min_abs(data.A.row(i), &ind);
			data.row_multi(i) = 1 / pow(row_max(i) * row_min(i), .5);
			data.A.row(i) = data.A.row(i) * data.row_multi(i);
			data.b(i) = data.b(i) * data.row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		find_NonZero(data.A.col(i), &ind);
		if (!ind.empty())
		{
			col_max(i) = max_abs(data.A.col(i), &ind);
			col_min(i) = min_abs(data.A.col(i), &ind);
			data.col_multi(i) = 1 / pow(col_max(i) * col_min(i), .5);
			data.A.col(i) = data.A.col(i) * data.col_multi(i);
			data.c(i) = data.c(i) * data.col_multi(i);
		}
	}
}
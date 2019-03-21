#include "pch.h"
#include <vector>
#include "ScalingMisc.h"
#include <Eigen/Dense>
#include "../ILPData.h"

using namespace std;

void IpNorm_p1(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_med(m);

	RowVectorXd col_med(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		find_NonZero(data.A.row(i),&ind);
		if (!ind.empty())
		{
			row_med(i) = med_abs(data.A.row(i), &ind);
			data.row_multi(i) = 1 / row_med(i);
			data.A.row(i) = data.A.row(i) * data.row_multi(i);
			data.b(i) = data.b(i) * data.row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		find_NonZero(data.A.col(i),&ind);
		if (!ind.empty())
		{
			col_med(i) = med_abs(data.A.col(i), &ind);
			data.col_multi(i) = 1 / col_med(i);
			data.A.col(i) = data.A.col(i) * data.col_multi(i);
			data.c(i) = data.c(i) * data.col_multi(i);
		}
	}
}
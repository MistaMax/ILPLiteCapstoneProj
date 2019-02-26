#include <vector>
#include <math.h>

using namespace std;

void debuchet_p2(ILPData data)
{
	vector<int> ind;
	int m = data.A.rows();
	int n = data.A.cols();

	RowVectorXd row_max(m);
	RowVectorXd row_multi(m);

	RowVectorXd col_max(n);
	RowVectorXd col_multi(n);

	for (int i = 0; i < m; i++) {
		//find nonzero elements of a row
		ind = find_NonZero(data.A.row(i));
		if (!ind.empty())
		{
			row_max(i) = max_abs(data.A.row(i), ind);
			row_multi(i) = 1 / row_max(i);
			data.A.row(i) = data.A.row(i) * row_multi(i);
			data.b(i) = data.b(i) * row_multi(i);
		}
	}

	for (int i = 0; i < n; i++) {
		//find nonzero elements of a row
		ind = find_NonZero(data.A.col(i));
		if (!ind.empty())
		{
			col_max(i) = max_abs(data.A.col(i), ind);
			col_multi(i) = 1 / col_max(i);
			data.A.col(i) = data.A.col(i) * col_multi(i);
			data.c(i) = data.c(i) * col_multi(i);
		}
	}
}
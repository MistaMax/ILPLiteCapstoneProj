#include <vector>
#include "scaling.h"

using namespace std;

vector<int> find_NonZero(RowVectorXd rowVector)
{
	vector<int> index;
	for (int i = 0; i < rowVector.cols(); i++)
	{
		if (rowVector(i) != 0)
			index.push_back(i);
	}
	return index;
}

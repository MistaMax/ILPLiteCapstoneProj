#include <vector>
#include "scaling.h"
#include <Eigen/Dense>
#include "ScalingMisc.h"

using namespace std;
using namespace Eigen;

void find_NonZero(RowVectorXd rowVector, vector<int> *index)
{
	for (int i = 0; i < rowVector.cols(); i++)
	{
		if (rowVector(i) != 0)
			(*index).push_back(i);
	}
}

double sum_abs(RowVectorXd rowVector, vector<int> *index)
{
	double sum = 0;

	for (int i = 0; i < (*index).size(); i++)
	{
		 sum += (double) abs(rowVector((*index)[i]));
	}
	return sum;
}

double sum_inv_abs(RowVectorXd rowVector, vector<int> *index)
{
	double sum = 0;
	for (int i = 0; i < (*index).size(); i++)
	{
		sum += (double)1 / abs(rowVector((*index)[i]));
	}
	return sum;
}

double sum_sqrd(RowVectorXd rowVector, vector<int> *index)
{
	double sum = 0;
	for (int i = 0; i < (*index).size(); i++)
	{
		sum += (double)pow(rowVector((*index)[i]),2);
	}
	return sum;
}

double sum_inv_sqrd(RowVectorXd rowVector, vector<int> *index)
{
	double sum = 0;
	for (int i = 0; i < (*index).size(); i++)
	{
		sum += (double)1 / pow(rowVector((*index)[i]), 2);
	}
	return sum;
}

double max_abs(RowVectorXd rowVector, vector<int> *index)
{
	double max = 0;
	for (int i = 0; i < (*index).size(); i++)
	{
		if (max < abs(rowVector((*index)[i])))
			max = abs(rowVector((*index)[i]));
	}
	return max;
}

double min_abs(RowVectorXd rowVector, vector<int> *index)
{
	double min = DBL_MAX;
	for (int i = 0; i < (*index).size(); i++)
	{
		if (min > abs(rowVector((*index)[i])))
			min = abs(rowVector((*index)[i]));
	}
	return min;
}

double med_abs(RowVectorXd rowVector, vector<int> *index)
{
	vector<double> orderedList;
	
	for (int i = 0; i < (*index).size(); i++)
	{
		orderedList.push_back(rowVector(i));
	}

	sort(orderedList.begin(), orderedList.end());
	
	int size = orderedList.size();
	if (size % 2 != 0)
		return (orderedList[(size / 2) - 1] + orderedList[size / 2]) / 2;
	return orderedList[size / 2];
}

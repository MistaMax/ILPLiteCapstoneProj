#pragma once
void find_NonZero(RowVectorXd rowVector, vector<int> *index);
double sum_abs(RowVectorXd rowVector, vector<int> *index);
double sum_inv_abs(RowVectorXd rowVector, vector<int> *index);
double sum_inv_sqrd(RowVectorXd rowVector, vector<int> *index);
double sum_sqrd(RowVectorXd rowVector, vector<int> *index);
double max_abs(RowVectorXd rowVector, vector<int> *index);
double min_abs(RowVectorXd rowVector, vector<int> *index);
double med_abs(RowVectorXd rowVector, vector<int> *index);
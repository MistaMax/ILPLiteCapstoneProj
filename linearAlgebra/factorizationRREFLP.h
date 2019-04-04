#pragma once
#include <iostream>
#include <string>
#include <cmath>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"

void addEqualityToRowIdx(SpMat *rowIdx, SpVec *a0, int m);
void getAbsMaxFromVec(SpVec *vec, double *maxVal, int *maxIdx);
//int factorizationRREF_LP(SpMat *A, SpVec *b, SpVec *Eq, int tol, matrixIndexList *out, SpMat *j_b);
int factorizationRREFLP(SpMat *A, SpVec *b, SpVec *Eq, long tol, SpVec *out, SpVec *j_b);
void removeValueFromVector(SpVec *vec, double value);
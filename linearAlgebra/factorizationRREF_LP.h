#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"

void addEqualityToRowIdx(SpMat *rowIdx, SpVec *a0, int m);
int factorizationRREF_LP(SpMat *A, SpVec *b, SpMat *Eq, int tol, matrixIndexList *out, SpMat *j_b);
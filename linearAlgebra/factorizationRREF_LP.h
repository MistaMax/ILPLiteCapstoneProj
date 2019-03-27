#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"

int factorizationRREF_LP(SpMat *A, SpVec *b, SpMat *A_eq, int tol, int *out, SpMat *j_b);
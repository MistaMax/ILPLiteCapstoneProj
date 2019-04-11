#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"
#include "linearAlgebra.h"
//return the solution
void matrixSolveLU(SpMat *A, SpVec *b, SpVec *X, SpMat *P);
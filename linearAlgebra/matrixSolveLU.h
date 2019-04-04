#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"
//return the solution
double matrixSolveLU(SpMat *A, SpVec *b, SpMat *P);
#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../Logger.h"
#include "../matrixTools/matrixTools.h"
#include "../linearAlgebra/linearAlgebra.h"

typedef struct output {
	SpVec x;
	double fVal;
	short exitFlag;
	int iter;
	SpVec bv;
}Output;

Output solveRevisedPrimalSimplex(ILPData *data);
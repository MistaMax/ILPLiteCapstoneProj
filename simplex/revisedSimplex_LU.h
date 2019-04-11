#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"

typedef struct revisedSimplexLUOut {
	SpVec x;
	double fVal;
	int iter;
}revisedSimplexLUOut;

void revisedSimplexLU(ILPData *data, revisedSimplexLUOut *output);
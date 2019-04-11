#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"
#include "../matrixTools/matrixTools.h"

void factorizationLU(SpMat *A, SpMat *L, SpMat *U, SpMat *P);
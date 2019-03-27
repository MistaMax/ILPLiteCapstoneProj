#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"

using namespace std;
SpMat genIdentityMatrix(int m, int n);
DenMat genDenseIdentityMatrix(int m, int n);
void addSlackToMatrix(SpMat *mat, int m, int n, int slackM, int slackN);
void addSlackToVector(SpVec *vec, int m, int slack);
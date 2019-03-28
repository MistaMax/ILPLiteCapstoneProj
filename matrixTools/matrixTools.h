#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"

using namespace std;
typedef struct matrixIndex {
	int m;
	int n;
} matrixIndex;

typedef struct matrixIndexNode {
	matrixIndex index;
	struct matrixIndexNode *next;
}matrixIndexNode;

typedef struct matrixIndexList {
	matrixIndexNode *start;
	matrixIndexNode *end;
	long size;
};

SpMat genIdentityMatrix(int m, int n);
DenMat genDenseIdentityMatrix(int m, int n);
void addSlackToMatrix(SpMat *mat, int m, int n, int slackM, int slackN);
void addSlackToVector(SpVec *vec, int m, int slack);
matrixIndexList *createIndexList();
matrixIndexNode *allocIndexNode();
void addIndexToList(matrixIndexList *list, int m, int n);
void freeIndexNode(matrixIndexNode *node);
void freeIndexList(matrixIndexList *list);
void findAllEqualities(SpVec *Eq, SpVec *a0);
void findAllInequalities(SpVec *Eq, SpVec *a0);
void constructEqualityVector(SpVec *origVec, SpVec *newVec, SpVec *a0);
void constructEqualityMatrix(SpMat *origMat, SpMat *newMat, SpVec *a0);
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "../ILPData.h"

#define ROW_VECTOR 1
#define COL_VECTOR 0

using namespace std;

typedef Triplet<double> T;
typedef vector<T> TripletVector;

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
} matrixIndexList;

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
void extractVectorFromMatrix(SpMat *mat, SpVec *vec, int start, int end, int index, int focus);
void alterMatrixColumnVector(SpMat *mat, int start, int end, int col, SpVec *insert);
void alterMatrixRowVector(SpMat *mat, int start, int end, int row, SpVec *insert);
void addZerosToColumnVector(SpMat *mat, int start, int end, int col);
void addZerosToRowVector(SpMat *mat, int start, int end, int row);
void printSparseMatrix(SpMat *mat);
void extractTripletsFromSparseMatrix(SpMat *mat, TripletVector *tVec);
void refreshSparseMatrix(SpMat *mat);
void insertValueIntoSparseMatrix(SpMat *mat, int row, int col, double val);
void insertZeroIntoSparseMatrix(SpMat *mat, int row, int col);
void addValueToVectorEnd(SpVec *vec, double val);
void removeZerosFromVector(SpVec *vec);
void genSubMatrixFromIndecies(SpMat *orig, SpMat *sub, SpVec *indecies, int focus);
void genSubVectorFromIndecies(SpVec *orig, SpVec *sub, SpVec *indecies);

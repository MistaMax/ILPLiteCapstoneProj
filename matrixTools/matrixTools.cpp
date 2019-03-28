#include "pch.h"
#include "matrixTools.h"

using namespace std;
SpMat genIdentityMatrix(int m, int n) {
	SpMat sparseIdentity = genDenseIdentityMatrix(m, n).sparseView();
	return sparseIdentity;
}

DenMat genDenseIdentityMatrix(int m, int n) {
	MatrixXd identity(m, n);
	identity = MatrixXd::Identity(m, n);
	return identity;
}

void addSlackToMatrix(SpMat *mat, int m, int n, int slackM, int slackN) {
	mat->conservativeResize(m + slackM, n + slackN);
	//add more code to initialize the zeros
}

void addSlackToVector(SpVec *vec, int m, int slack) {
	vec->conservativeResize(m + slack);
}
//CONVERT LINKED LIST STUFF TO CLASSES USING DECONSTRUCTORS
//LATER TO AVOID MEMORY LEAKS
matrixIndexList *createIndexList() {
	matrixIndexList *list;
	list = (matrixIndexList *)malloc(sizeof(matrixIndexList));
	list->end = NULL;
	list->start = NULL;
	list->size = 0;
	return list;
}

matrixIndexNode *allocIndexNode() {
	return (matrixIndexNode *)malloc(sizeof(matrixIndexNode));
}

void addIndexToList(matrixIndexList *list, int m, int n) {
	matrixIndexNode *node = allocIndexNode();
	node->index.m = m;
	node->index.n = n;
	node->next = NULL;
	if (list->size != 0) {
		list->end->next = node;
	}
	else {
		list->start = node;
	}
	list->end = node;
	list->size++;
}

void freeIndexNode(matrixIndexNode *node) {
	free(node);
}

void freeIndexList(matrixIndexList *list) {
	matrixIndexNode *next;
	for (matrixIndexNode *p = list->start; p != NULL;p=next) {
		next = p->next;
		freeIndexNode(p);
	}
	free(list);
}

void findAllEqualities(SpVec *Eq, SpVec *a0) {
	int m = Eq->rows() - Eq->nonZeros();
	SpVec vec(m);
	int j = 0;
	for (int i = 0; i < Eq->rows(); i++) {
		if (j >= m)break;
		if (Eq->coeff(i) == 0) {
			vec.coeffRef(j) = Eq->coeff(i);
			j++;
		}
	}
	*a0 = vec;
}

void findAllInequalities(SpVec *Eq, SpVec *a0) {
	int m = Eq->nonZeros();
	SpVec vec(m);
	int j = 0;
	for (int i = 0; i < Eq->rows(); i++) {
		if (j >= m)break;
		if (Eq->coeff(i) != 0) {
			vec.coeffRef(j) = Eq->coeff(i);
			j++;
		}
	}
	*a0 = vec;
}

void constructEqualityMatrix(SpMat *origMat, SpMat *newMat, SpVec *a0) {
	int m, n;
	m = a0->rows();
	n = origMat->cols();
	SpMat mat(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			mat.coeffRef(i, j) = origMat->coeff(a0->coeff(i), j);
		}
	}
	*newMat = mat;
}

void constructEqualityVector(SpVec *origVec, SpVec *newVec, SpVec *a0) {
	int m;
	m = a0->rows();
	SpVec vec(m);
	for (int i = 0; i < m; i++) {
		vec.coeffRef(i) = origVec->coeff(a0->coeff(i));
	}
	*newVec = vec;
}
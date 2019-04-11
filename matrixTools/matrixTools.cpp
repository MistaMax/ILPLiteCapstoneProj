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
	a0->resize(m);
	int j = 0;
	for (int i = 0; i < Eq->rows(); i++) {
		if (j >= m)break;
		if (Eq->coeff(i) == 0) {
			a0->coeffRef(j) = Eq->coeff(i);
			j++;
		}
	}
}

void findAllInequalities(SpVec *Eq, SpVec *a0) {
	int m = Eq->nonZeros();
	a0->resize(m);
	int j = 0;
	for (int i = 0; i < Eq->rows(); i++) {
		if (j >= m)break;
		if (Eq->coeff(i) != 0) {
			a0->coeffRef(j) = Eq->coeff(i);
			j++;
		}
	}
}

void constructEqualityMatrix(SpMat *origMat, SpMat *newMat, SpVec *a0) {
	int m, n;
	m = a0->rows();
	n = origMat->cols();
	newMat->resize(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			newMat->coeffRef(i, j) = origMat->coeff(a0->coeff(i), j);
		}
	}
}

void constructEqualityVector(SpVec *origVec, SpVec *newVec, SpVec *a0) {
	int m;
	m = a0->rows();
	newVec->resize(m);
	for (int i = 0; i < m; i++) {
		newVec->coeffRef(i) = origVec->coeff(a0->coeff(i));
	}
}

//focus:
// 0 - column vector
// 1 - row vector
void extractVectorFromMatrix(SpMat *mat, SpVec *vec, int start, int end, int index, int focus) {
	vec->resize(end - start + 1);
	int subVecIndex = 0;

	if (focus == COL_VECTOR) {
		for (int i = start; i <= end; i++) {
			if(mat->coeff(i,index) !=0 )
				vec->coeffRef(subVecIndex) = mat->coeff(i, index);
			subVecIndex++;
		}
	}
	else if (focus == ROW_VECTOR) {
		for (int i = start; i <= end; i++) {
			if (mat->coeff(index, i) != 0)
				vec->coeffRef(subVecIndex) = mat->coeff(index, i);
			subVecIndex++;
		}
	}
}

void alterMatrixColumnVector(SpMat *mat, int start, int end, int col, SpVec *insert)
{
	int vecIndex = 0;
	for (int i = start; i <= end; i++) {
		mat->coeffRef(i, col) = insert->coeff(vecIndex);
		vecIndex++;
	}
	refreshSparseMatrix(mat);
}

void alterMatrixRowVector(SpMat *mat, int start, int end, int row, SpVec *insert)
{
	int vecIndex = 0;
	for (int i = start; i <= end; i++) {
		mat->coeffRef(row, i) = insert->coeff(vecIndex);
		vecIndex++;
	}
	refreshSparseMatrix(mat);
}

void addZerosToColumnVector(SpMat *mat, int start, int end, int col)
{
	//insert zeros
	for (int i = start; i <= end; i++) {
		insertZeroIntoSparseMatrix(mat, i, col);
	}
	//efficiency idea, extract all the triplets that are not within the range
	mat->makeCompressed();
	//remove zero references
	refreshSparseMatrix(mat);
}

void addZerosToRowVector(SpMat *mat, int start, int end, int row)
{
	//insert zeros
	cout << "Matrix Before:" << endl << *mat << endl;
	for (int i = start; i <= end; i++) {
		insertZeroIntoSparseMatrix(mat, row, i);
	}
	cout << "Matrix With Added Zeros:" << endl << *mat << endl;
	mat->makeCompressed();
	cout << "Compressed Matrix With Zeros:" << endl << *mat << endl;
	//completely update the sparse matrix
	refreshSparseMatrix(mat);
	cout << "Refreshed Sparse Matrix Without Zeros:" << endl << *mat << endl;
}

void printSparseMatrix(SpMat *mat) {
	cout << "Row\tCol\tVal" << endl;
	for (int k = 0; k < mat->outerSize(); ++k)
	{
		for (SparseMatrix<double>::InnerIterator it((*mat), k); it; ++it)
		{
			cout << 1 + it.row() << "\t"; // row index
			cout << 1 + it.col() << "\t"; // col index (here it is equal to k)
			cout << it.value() << endl;
		}
	}
}

void extractTripletsFromSparseMatrix(SpMat *mat, TripletVector *tVec)
{
	for (int k = 0; k < mat->outerSize(); ++k) {
		for (SparseMatrix<double>::InnerIterator it(*mat, k); it; ++it) {
			if(it.value() != 0)
				tVec->push_back(T(it.row(),it.col(),it.value()));
		}
	}
}
//removes all the zero references from the sparse matrix
void refreshSparseMatrix(SpMat *mat) {
	mat->prune(0,0);
}

void insertValueIntoSparseMatrix(SpMat *mat, int row, int col, double val)
{
	mat->coeffRef(row, col) = val;
}

void insertZeroIntoSparseMatrix(SpMat *mat, int row, int col) {
	mat->coeffRef(row, col) = 0;
}

void addValueToVectorEnd(SpVec *vec, double val)
{
	int m = vec->rows();
	vec->conservativeResize(m+1);
	vec->coeffRef(m) = val;
}

void removeZerosFromVector(SpVec *vec)
{
	/*SpVec nonZeroVector(vec->nonZeros());
	int vectorIndex = 0;
	for (int i = 0; i < vec->rows(); i++)
	{
		if (vec->coeff(i) != 0) {
			nonZeroVector.coeffRef(vectorIndex) = vec->coeff(i);
			vectorIndex++;
		}
		if (vectorIndex == vec->nonZeros())break;
	}
	*vec = nonZeroVector;*/
	vec->prune(0, 0);
}

void genSubMatrixFromIndecies(SpMat *orig, SpMat *sub, SpVec *indecies, int focus)
{
	int m, n;
	if (focus == COL_VECTOR) {
		m = orig->rows();
		n = indecies->rows();
		sub->resize(m, n);
		for (int i = 0; i < n; i++) {
			SpVec tmp;
			extractVectorFromMatrix(orig, &tmp, 0, m - 1, indecies->coeff(i), focus);
			alterMatrixColumnVector(sub, 0, m - 1, i, &tmp);
		}
	}
	else if (focus == ROW_VECTOR)
	{
		m = indecies->rows();
		n = orig->cols();
		sub->resize(m, n);
		for (int i = 0; i < m; i++) {
			SpVec tmp;
			extractVectorFromMatrix(orig, &tmp, 0, n - 1, indecies->coeff(i), focus);
			alterMatrixRowVector(sub, 0, n - 1, i, &tmp);
		}
	}
}
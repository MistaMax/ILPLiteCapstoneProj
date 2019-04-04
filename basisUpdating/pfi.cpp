#include "pch.h"
#include "pfi.h"
#include "../Logger.h"
using namespace std;
//figure out how to create an identity matrix for sparse without having
// to create dense matricies and converting
void pfi(SpMat *basisInv, SpVec *h_1, int r) {
	//compute the eta column vector (Eq. 7.3)
	SpVec eta = (-(*h_1))/h_1->coeff(r);
	eta.coeffRef(r) = 1 / h_1->coeff(r);
	//create a dense identity matrix
	MatrixXd dense_eta_inv(basisInv->rows(),basisInv->cols());
	dense_eta_inv = MatrixXd::Identity(basisInv->rows(), basisInv->cols());
	//convert the generated dense identity matrix to a sparse matrix
	dense_eta_inv.row(r) = VectorXd(eta);
	SpMat eta_inv = dense_eta_inv.sparseView();

	//use set identity and add in the vector instead
	//eta_inv.setIdentity();
	
	//Update Basis Inverse
	*basisInv = eta_inv * (*basisInv);
}
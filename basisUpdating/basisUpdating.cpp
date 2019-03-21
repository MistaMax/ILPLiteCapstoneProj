#include "pch.h"
#include "basisUpdating.h"
#include "pfi.h"

using namespace std;

void basisUpdate(SpMat *basisInv, SpVec *h_1, int r) {
	//add on to basis update with the config
	pfi(basisInv, h_1, r);
}
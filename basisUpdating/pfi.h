#pragma once
#include <iostream>
#include <string>
#include "../ILPData.h"

/*
% Product Form of the Inverse basis update method.
%
% Description:
%   Product Form of the Inverse basis update method.
%   Adaptation of code by Ploskas, N., & Samaras, N.
%
% Syntax:
%   BasisInv = pfi(BasisInv, h_l, r)
%
% Parameters:
%	BasisInv:   matrix with the basis inverse (size m x m)
%	h_l:        vector with pivot column (size m x 1)
%	r:          the index of the leaving variable
%
% Return values:
%	BasisInv:   matrix with the new basis inverse
%               (size m x m)
%
% Reference:
%   - Ploskas, N., & Samaras, N. "Linear Programming Using Matlab",
%     Springer, 2017.
%
% Notes:
% - Other m-files required: (several)
% - Subfunctions: none
% - MAT-files required: none
%

% Author(s):	P.R.
% email:    	ilplite2018@gmail.com
% Website:     	https://github.com/ilplite2018/ilplite
%
% Copyright �, 2018 ILP-Lite,  All rights reserved.
%
% This program carries no warranty, not even the implied
% warranty of merchantability or fitness for a particular purpose.
%
% Please email bug reports or suggestions for improvements to:
% ilplite2018@gmail.com
%
*/

void pfi(SpMat *basisInv, SpVec *h_1, int r);
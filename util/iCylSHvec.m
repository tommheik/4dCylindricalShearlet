function x = iCylSHvec(C, S, pyrMode, F)
% ICYLSHVEC provides inverse/adjoint of cylindrical shearlet transform of
% 4-D data with coefficients stored in a single vector C.
% Input: C       Coefficient vector given by CylSHvec
%        S       Default size of the coefficient array cells
%        pyrMode 1,1.5 or 2. Default to 1.
%        F       Optional synthesis filters for adjoint. Otherwise use
%                inverse transform.
%
% Output: x      Single vector containing the 4-D data
%
% Tommi Heikkilä
% Created 25.5.2021
% Last updated 25.5.2021

if nargin < 2
    error('Too few input arguments')
end
if nargin > 4
    error('Too many input arguments')
end
if nargin < 3
    pyrMode = 1;
end
if nargin < 4
    type = "inverse";
else
    type = "adjoint";
end

level = size(S,1)-1; % Infer decomposition level
smoothFun = @rcos;

%%% Reorganize coefficients %%%
coeff = cell(1, level+1);
for l = 1:level+1
    j = prod(S(l,:));
    coeff{l} = reshape(C(1:j),S(l,:));
    C(1:j) = [];
end

%%% Inverse or adjoint transform %%%
switch type
    case "inverse"
        BPrec = CylShearRec4D(coeff);
    case "adjoint"
        BPrec = CylShearAdj4D(coeff,F);
end

%%% Laplace pyramid reconstruction %%%

x = PyrNDRec_mm(BPrec, 'S', pyrMode, smoothFun);

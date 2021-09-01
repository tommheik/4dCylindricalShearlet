function C = CylSHvec(x, S, F, pyrMode)
% CYLSHVEC provides Cylindrical shearlet transform of 4-D data with
% coefficients stored into a single vector C
% Input: x       4-D object we want to decompose with cylindrical shearlets
%        S       Default size of the coefficient array cells
%        F       Meyer decomposition filters
%    Laplace pyramid stuff:
%        pyrMode 1,1.5 or 2. Default to 1.
%
% Output: C Single vector containing all coefficients
%
% Tommi Heikkilä
% Created 25.5.2021
% Last updated 25.5.2021

% Specific function to drop things into vectors
vec  = @(x) x(:);

if nargin < 4
    pyrMode = 1;
end
if nargin < 3
    error('Too few input arguments')
end
if nargin > 4
    error('Too many input arguments')
end

level = length(F);
smoothFun = @rcos;

%%% Laplace pyramid decomposition %%%

BP = PyrNDDec_mm(x, 'S', level, pyrMode, smoothFun);
% Note that the output is in 'S'patial domain in order to properly size the
% BP data and the filters F for FFT-type convolution.
BP = cellfun(@single,BP,'UniformOutput',false); % Case to single in a clumsy way

%%% Cylindrical shearlet decomposition %%%

coeff = CylShearDec4D(BP,F);

%%% Organize into one vector %%%

C = zeros(sum(prod(S,2)),1,'single');
i = 0;
for l = 1:level+1
    j = prod(S(l,:));
    C(i+1:i+j) = coeff{l}(:);
    i = i+j;
end
end

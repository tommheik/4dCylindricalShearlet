function BP = CylShearRec4D(coeff)
%CYLSHEARREC4D performs the 4D cylindrical shearlet reconstruction.
%   CylShearRec4D is the function which corresponds to reconstruction. The
%   coefficients coeff are summed over different directions with respect to
%   the scale or level 1 <= l <= L. Low frequency coefficients (level L+1)
%   are not affected.
% 
%   The output is the Laplacian pyramid bandpass array which can be
%   reconstructed using PyrNDRec.m.
%
% INPUT
%  coeff    : 4D Cylindrical shearlet coefficients organized like F into
%             5D arrays for each level (except for L + 1 which is 4D).
%
% OUTPUT
%  BP       : Spatial 4D bandpass data at predetermined level. 
%
% T. Heikkilä   2021

L = length(coeff)-1;
sum5 = @(x) sum(x,5);
% Sum over different directions (5th dimension of the array)
BP = cellfun(sum5,coeff(1:L),'UniformOutput',false);
% Add low frequnecy part
BP(L+1) = coeff(L+1);
end


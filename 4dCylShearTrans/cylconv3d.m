function z = cylconv3d(F, g, outSz)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% CYLCONV3D performs a Fourier side cylindrical convolution with respect
% to the first 3 dimensions of F and g.
% 
% Input
%   F       : 3D or 4D array of correct size already in the Fourier domain
%   g       : 3D array of original size in the spatial domain
%   outSz   : Desired size of the output z
%
% Output
%   z       : Convolution of size outSz, real valued 3D or 4D array and 
%             in the spatial domain.
% 
% T. Heikkilä   2021
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if ismatrix(F) || ndims(F) > 4
    error('F is meant to be 4D (or 3D) array!')
end
if ndims(g) ~= 3
    error('g must be 3D array, not %d D!',ndims(g));
end
szF = size(F); % F is already extended so we can use these dimensions
szg = size(g); % To revert the extension we can use original size of g

% Zero-extend g
gExt = zeros(szF(1:3));
gExt(1:szg(1),1:szg(2),1:szg(3)) = g;

% Fourier transform gExt
g = fftn(gExt);

% Pointwise multiply (corresponds to spatial convolution). Then inverse
% Fourier transform with respect to the first 3 dimensions.

% This is the most computationally intensive part of the transform so we
% need to be clever about it.

% We revert the extension and cut the output to size
szg = floor(szg/2);
n1 = szg(1) + (1:outSz(1));
n2 = szg(2) + (1:outSz(2));
n3 = szg(3) + (1:outSz(3));

H = F .* g; % Pointwise multiply (dimensions of F and G can be different)
if ndims(H) == 3 % F is 3D
    F = ifftn(H,'symmetric');
else             % F is 4D
    F = ifft(ifft(ifft(H,[],3),[],2),[],1,'symmetric');
end
z = F(n1,n2,n3,:);
end

function BP = CylShearAdj4D(coeff, F)
%CYLSHEARADJ4D performs the 4D cylindrical shearlet synthesis (adjoint).
%   CylShearAdj4D is the function which corresponds to the adjoint. The
%   coefficients coeff are convolved (using FFT) against the respective 
%   dual filters of F over all scales or level 1 <= l <= L. Low frequency
%   coefficients (level L+1) are not affected.
%
%   Since the filters are (approximately) symmetric (at least if they were
%   of odd length) and real-valued, the filters F work as the dual filters.
% 
%   The putput is a Laplacian pyramid bandpass array which can be
%   reconstructed using PyrNDRec.m because the implementation is unitary.
%
% INPUT
%  coeff    : 4D Cylindrical shearlet coefficients organized like F into
%             5D arrays for each level (except for L + 1 which is 4D).
%  f        : 3D Meyer type cylindrical shearlet filters stored in spatial
%             domain and in 4D arrays.
%
% OUTPUT
%  BP       : Spatial 4D bandpass data at predetermined level. 
%
% T. Heikkilä   2022

% Error checks
dataClass = class(coeff{1});
L = length(coeff) - 1;

if L > length(F)
    error('Bandpass decomposition level: %d is too large for available filter level: %d.',L,length(F));
end
if L < length(F)
    warning('Bandpass decomposition level: %d is smaller than available filter level: %d.',L,length(F));
end
if ndims(coeff{1}) ~= 5
    error('Expected coefficient array to be 5D!');
end
if ndims(coeff{L+1}) ~= 4
    error('Low frequency cube should be 4D!');
end

%%% Synthesis
BP = cell(L + 1,1); % Bandpass arrays are stored based on level.
BP{L + 1} = coeff{L + 1}; % Central low frequency region
for l = 1:L
    szF = size(F{l}); % Size of any filter F
    numF = szF(4); % Number of filters in level l
    szF = szF(1:3); % No need to store number of filters here.
    
    szCoeff = size(coeff{l}); % Coeff array size. This will also be the BP array size.
    BP{l} = zeros(szCoeff(1:4), dataClass); % Initialize coefficient array
    
    % Precomputing FFT doesn't help but this way we can use the same
    % cylindrical convolution function as in decomposition.
    exSize = szF + szCoeff(1:3) - 1; % Extended size for no overlap
    
    % We revert the extension and cut the output to size
    offset = floor(szF/2);
    n1 = offset(1) + (1:szCoeff(1));
    n2 = offset(2) + (1:szCoeff(2));
    n3 = offset(3) + (1:szCoeff(3));
    
    % Initialize H
    H = complex(zeros(exSize(1:3),'single'));
    
    for fi = 1:numF % Loop through all filters.
        % Cylindrical 3D FFT of coefficient array
        C = fft(fft(fft(coeff{l}(:,:,:,:,fi),exSize(1),1),exSize(2),2),exSize(3),3);
        
        % Cylindrical 3D FFT of a filter
        G = fftn(F{l}(:,:,:,fi),exSize(1:3));
        
        % Pointwise multiply (corresponds to spatial convolution). Since
        % Fourier transform is linear we can first take the sum

        H =  H + G .* C; % Pointwise multiply (dimensions of F and G can be different)
    end % fi (filterIndex)
    
    h = ifft(ifft(ifft(H,[],3),[],2),[],1,'symmetric');
    BP{l} = h(n1,n2,n3,:); % Remove extension
end % l (decomposition level)
end


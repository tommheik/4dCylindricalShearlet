function BP = CylShearAdj4Dpar(coeff, F)
%CYLSHEARADJ4D performs the 4D cylindrical shearlet synthesis (adjoint)
%using parallel computing.
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
%   This implementation uses parallel for-loop for the most expensive step.
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
% T H   2021

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
    Fl = F{l};
    szF = size(Fl); % Size of any filter F
    numF = szF(4); % Number of filters in level l
    szF = szF(1:3); % No need to store number of filters here.
    
    szCoeff = size(coeff{l}); % Coeff array size. This will also be the BP array size.
    BPl = zeros(szCoeff(1:4), dataClass); % Initialize coefficient array
    
    % Precomputing FFT doesn't help but this way we can use the same
    % cylindrical convolution function as in decomposition.
    exSize = szF + szCoeff(1:3) - 1; % Extended size for no overlap
    % Zero-extend all 4D coeff layers in the first 3 dimensions. (Coeff is
    % 5D array)
    exCoeff = exindex(coeff{l}, 1:exSize(1), 1:exSize(2), 1:exSize(3), ':', ':', {0});
    
    parfor fi = 1:numF % Loop through all filters.
        layer = exCoeff(:,:,:,:,fi); % 4D coefficient array
        % Cylindrical 3D FFT
        C = fft(fft(fft(layer,[],1),[],2),[],3);
        
        % Convolve first 3 dimensions againt a filter F
        layer = cylconv3d(C,Fl(:,:,:,fi),szCoeff(1:3));
        % Sum up each layer of the level
        BPl = BPl + layer;
    end % fi (filterIndex)
    BP{l} = BPl;
end % l (decomposition level)
end


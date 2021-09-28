function coeff = CylShearDec4Dgpu(BP, F)
%CYLSHEARDEC4DGPU performs the 4D cylindrical shearlet decomposition on GPU
%   CylShearDec4D is the function for the corresponding decomposition. The
%   bandpass data BP is decomposed at given level using Meyer filters F
%   organized as in FIndex.
%
%   The actual decomposition is carried out by performing convolutions
%   between BP and F. For computational efficiency this is done using FFT.
%   The FFT is only carried out in 3D (cylindrically).
%
%   This implementation uses GPU to speed up the FFT convolution.
%
% INPUT
%  BP       : Spatial 4D bandpass data at predetermined level. 
%  F        : 3D Meyer type cylindrical shearlet filters stored in spatial
%             domain and in 4D arrays.
%
% OUTPUT
%  coeff    : 4D Cylindrical shearlet coefficients organized like F into
%             5D arrays for each level (except for level + 1 which is 4D).
%
% T H   2021
%

%%% Basic error checks
dataClass = class(BP{1}); % Bandpass data type
level = length(BP)-1; % Decomposition level.

if level > length(F)
    error('Bandpass decomposition level: %d is too large for available filter level: %d.',level,length(F));
end

if level < length(F)
    warning('Bandpass decomposition level: %d is smaller than available filter level: %d.',level,length(F));
end

%%% Decomposition
coeff = cell(level+1,1); % Coefficients are stored based on level.
coeff{level+1} = BP{level + 1}; % Central low frequency region
for l = 1:level
    szF = size(F{l}); % Size of any filter F
    numF = szF(4); % Number of filters in level l
    szF = szF(1:3); % No need to store number of filters here.
    
    szBP = size(BP{l}); % Bandpass layers size. This will also be the coefficient array size.
    
    % Since each filter is of identical size the FFT of BP can be
    % precomputed for efficiency.
    exSize = szF + szBP(1:3) - 1; % Extended size for no overlap
    % Zero-extend 4D BP layer in the first 3 dimensions.
    exBP = exindex(BP{l}, 1:exSize(1), 1:exSize(2), 1:exSize(3), ':', {0});
    
    % Obtain GPUarrays
    BPgpu = gpuArray(exBP);
    Fgpu = gpuArray(F{l});
    coeffgpu = gpuArray(zeros([szBP,numF], dataClass)); % Initialize coefficient array
    
    % Cylindrical 3D FFT
    BPgpu = fft(fft(fft(BPgpu,[],1),[],2),[],3);
    
    for fi = 1:numF % Loop through all filters.
        % "Convolve" (using FFT) the bandpass layer with each filter F.
        coeffgpu(:,:,:,:,fi) = cylconv3d(BPgpu,Fgpu(:,:,:,fi),szBP(1:3));
    end % fi (filterIndex)
    % Gather the gpuArray back to cpu
    coeff{l} = gather(coeffgpu);
end % l (decomposition level)


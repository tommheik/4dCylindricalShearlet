% Test file for 4D cylindrical shearlets.
% 
% T H    2021
%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all
close all
tic

%% 1. Set up the target object
N = 32; % Spatial (X, Y, Z) resolution
T = 16; % Temporal resolution

% Create a dynamic Shepp-Logan phantom
% addpath('G:\DynamicCT\simulated data');
% [~, f] = dynamicSheppLogan(N,1,T,15);
% rmpath('G:\DynamicCT\simulated data');

% Create 4D object made of random cube-regions
f = 0.5*hypercube([N N N T]);

%% 2. Set up the cyl-shearlet system

addpath('../BP'); % Laplace pyramid (bandpass) codes
addpath('../4DShearTrans'); % Shearlet transforms

level = 3; % Level of shearlet decomposition
dBand = 2.^(ceil((level+1:-1:2)'/2)+1); % Number of shearing directions per level
% The number of directions can also be two values for K1 and K2 (per level)
filterSize = 24*ones(1,level);
dataClass = 'single';

%% 3. Generate filters

% Directional filters stored in 3D arrays. Filter indicies given by FIndex
[F, FIndex] = GetMeyerBasedFilter(level,dBand,filterSize,dataClass);

%% 4. Cylindrical Shearlet transform

% Perform the Laplace pyramid decomposition
smooth_func = @rcos;
Pyr_mode = 1; %1; % This determines suitable input sizes!
BP = PyrNDDec_mm(f, 'S', level, Pyr_mode, smooth_func);
% Note that the output is in 'S'patial domain in order to properly size the
% BP data and the filters F for FFT-type convolution.
BP = cellfun(@single,BP,'UniformOutput',false); % Case to single in a clumsy way

% Perform shearlet decomposition
coeff = CylShearDec4D(BP,F);


%% 5. Cylindrical Shearlet reconstruction

% Perform shearlet reconstruction
BPrec = CylShearRec4D(coeff);

% Perform the Laplace pyramid reconstruction (note input is 'S'patial)
rec = PyrNDRec_mm(BPrec, 'S', Pyr_mode, smooth_func);

%% 6. Cylindrical Shearlet adjoint

% Perform shearlet adjoint
BPadj = CylShearAdj4D(coeff,F);

% Perform the Laplace pyramid adjoint(same as reconstruction)
adj = PyrNDRec_mm(BPadj, 'S', Pyr_mode, smooth_func);

%% n. Total time
totTime = toc

errRec = norm(f(:)-rec(:))

%% n + 1. Compare inner products
% Note that this should be done with two random elements instead of just f
% and SHf.
ipSpat = dot(f(:),adj(:));
ipSh = 0;
for l = 1:level+1
    ipSh = ipSh + norm(coeff{l}(:))^2;
end
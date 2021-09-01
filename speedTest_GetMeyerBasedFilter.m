% This is a test file for speed comparison between original
% GetMeyerBasedFilter function and the new one used in 4D cylindrical
% shearlets.
%
% T H    2021

%%%%
clear all
close all

%% Problems
DecLevels = [4]; % Decomposition levels
dBand={{[ 8  8]}, ... %%%%for level =1
        {[8 8 ],[6 6]}, ...  %%%% for level =2
        {[8 8 ], [6 6],[4 4]}, ...   %%%% for level =3
        {[8 8],[8 8],[4 4],[4 4]}}; %%%%% for level =4
filterSize = [24,24,24,24];
dataClass = 'single';

%% Original function
tic
addpath('G:\3dshearlet-master\3DShearTrans')
for iii = 1:size(filterSize,1)
    flSz = filterSize(iii,:);
    for level = DecLevels
        F = GetMeyerBasedFilter(level, dBand, flSz, dataClass);
    end
end
tOrginial = toc
rmpath('G:\3dshearlet-master\3DShearTrans')

%% Updated function
tic
addpath('G:\4dCylindricalShearlet\4DShearTrans')
for iii = 1:size(filterSize,1)
    flSz = filterSize(iii,:);
    for level = DecLevels
        [F, fIndex] = GetMeyerBasedFilter(level, dBand, flSz, dataClass);
    end
end
tUpdated = toc
rmpath('G:\4dCylindricalShearlet\4DShearTrans')
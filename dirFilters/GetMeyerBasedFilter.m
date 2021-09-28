%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% function [F, FIndex] = GetMeyerBasedFilter(level,dBand,filterSize,dataClass)
% Generates windowing filters
% Input:   
%        level      : In multilevel decomposition number of levels
%        dBand      : number of shearing directions k1 and k2
%        filterSize : 3D side length of the filter
%        dataClass  : 'single' or 'double'
% Output: 
%        F          : Windowing filter at different level (stored as 3D
%                     arrays because these are constant along 4th dimension.
%                     This saves computer memory.
%        FIndex     : Indexing array for all of the filters, stored as uint8
%
% This is a slightly modified version of the GetMeyerBasedFilter function
% created for the 3D Shearlet Transform by P. Negi and D. Labate
%
% T H   2021
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

function [F, FIndex] = GetMeyerBasedFilter(level,dBand,filterSize,dataClass)
if nargin < 4 % Default is single precision
    dataClass = 'single';
end
% Initialize as cell arrays for the filter sizes differ between levels
F=cell(1,level);  
FIndex=cell(1,level);  

for l=1:level  

    cubeSize=filterSize(l); % Size of the 3D filter cube
    % K1, K2 = number of shearing directions
    if isa(dBand,'cell') && isa(dBand{1},'cell')
        numDir=dBand{level}{l}(1,:); % Old format
    else
        numDir = dBand(l,:); % Simple format
    end

    if length(numDir) == 1 % Only one value passed: K1 = K2
        numDir(2) = numDir;
    end

    % Split the Fourier domain into pairs of pyramids. The array of repeated
    % indicies is not used (originally given by PolarToRec using PolFreq).
    P = GeneratePyramidSection(cubeSize);
    shift = floor(cubeSize ./ numDir);

    fNum = numDir(1)*numDir(2)*3; % Total number of filters
    % Array for indexing filters based on directions k1 and k2 and Fourier
    % domain pyramid p = 1,2 or 3:
    FIndex{l} = reshape(uint8(1:fNum),[numDir,3]);

    % Initialize all filters for the level
    F{l} = zeros(cubeSize, cubeSize, cubeSize, fNum, dataClass);

    A=zeros(cubeSize,cubeSize,cubeSize,dataClass); % Array for normalizing
    % Quote from the original GetMeyerBasedFilter:
    %  "Building Meyer filter in 3-d radial grid
    %   Think of it as 3-d rectangle. Middle radial, coordinates goes along the length.
    %   Center has response 1.
    %   As one moves away from the center, filter response decreases (check
    %   Meyer filter description)."

    % Directional filters depend on parameters k1 and k2. One can think of them
    % in a grid where k1 gives the row and k2 the column. Then there are 9
    % configurations:
    %   1 central (most of the values of k1 and k2)
    %   4 edges (2 horizontal, 2 vertical)
    %   4 corners
    % However we only need to consider 8 of them because we can do the left
    % edge and central region at once: (here C# denotes case #)
    %           C3 C2 C7
    %           C1 C1 C6
    %           C5 C4 C8
    %
    % NOTE: the ordering of k1 and k2 is switched compared to l1 and l2 used in
    % the 3D Shearlet transform counterpart of GetMeyerBasedFilter. This
    % shouldn't be more than a matter of preference.

    mRadial = ones(shift(1)+1,cubeSize,shift(2)+1,dataClass);
    mRadial([1 shift(1)+1], :, :) = .5; % First and last X-value
    mRadial(:, :, [1 shift(2)+1]) = .5; % First and last Z-value

    %%% 1. case
    for k1 = 2:numDir(1)-1
    for k2 = 1:numDir(2)-1 % Note that k2 = 1 is included here!
    %%%
      % mRadialIdx specifies radial region boundary for filter with orientation k1, k2
      % k1 controls first (i) radial coordinates and k2 controls third (j) coordinates
      mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1)+1; 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2)+1 ];
      for p=1:3 % Fourier pyramid pair
        fi = FIndex{l}(k1,k2,p); % Filter index
        F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
        A = A + F{l}(:,:,:,fi); % Add to normalizing array
      end % p
    end % k1
    end % k2

    %%% 2. case
    % Same mRadial as 1. case
        k1 = 1;
    for k2 = 2:numDir(2)-1
        mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1)+1; 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2)+1 ];
      for p=1:3 % Fourier pyramid pair
        fi = FIndex{l}(k1,k2,p); % Filter index
        F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
        A = A + F{l}(:,:,:,fi); % Add to normalizing array
      end % p
    end % k2

    %%% 3. case
    mRadial(1, :, 1) = 1/3; % First X and Z values
    k1 = 1;
    k2 = 1;
    %%%
    mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1)+1; 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2)+1 ];

    for p = 1:3 % Fourier pyramid pair
      fi = FIndex{l}(k1,k2,p); % Filter index
      F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
      A = A + F{l}(:,:,:,fi); % Add to normalizing array
    end % p

    %%% 4. case
    % Here the X-dimension is smaller so we can do that by removing X = 1. This
    % also reverts the changes in 3. case!
    mRadial(1,:,:) = []; % Remove first row: mRadial = shift(1) x numDir x shift(2) + 1
    mRadial(1,:,:) = .5; % First (and last) X-value
        k1 = numDir(1);
    for k2 = 2:numDir(2)-1 
    %%%
      % Note how the shorter X-dimension is taken into account!
      mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1); 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2)+1 ];

      for p=1:3 % Fourier pyramid pair
        fi = FIndex{l}(k1,k2,p); % Filter index
        F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
        A = A + F{l}(:,:,:,fi); % Add to normalizing array
      end % p
    end % k2

    %%% 5. case
    mRadial(shift(1),:,1) = 1/3; % Last X value, first Z value = 1/3
    k1 = numDir(1);
    k2 = 1;
    %%%
    % Note how the shorter X-dimension is taken into account!
    mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1) ;1 cubeSize ; (k2-1)*shift(2)+1  k2*shift(2)+1  ];

    for p=1:3 % Fourier pyramid pair
      fi = FIndex{l}(k1,k2,p); % Filter index
      F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
      A = A + F{l}(:,:,:,fi); % Add to normalizing array
    end % p

    %%% 6. case
    % This is like case 4 but X and Z are switched.
    mRadial = ones(shift(1)+1,cubeSize,shift(2),dataClass);
    mRadial([1 shift(1)+1], :, :) = .5; % First and last X-value
    mRadial(:, :, [1 shift(2)]) = .5;   % First and last Z-value

        k2 = numDir(2);
    for k1 = 2:numDir(1)-1
    %%%
      % Note how the shorter Z-dimension is taken into account!
      mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1)+1; 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2) ];

      for p=1:3 % Fourier pyramid pair
        fi = FIndex{l}(k1,k2,p); % Filter index
        F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
        A = A + F{l}(:,:,:,fi); % Add to normalizing array
      end % p
    end % k1

    %%% 7. case
    mRadial(1, :, shift(2)) = 1/3; % First X value, last Z value
    k2 = numDir(2);
    k1 = 1;
    %%%
    % Note how the shorter Z-dimension is taken into account!
    mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1)+1; 1 cubeSize; (k2-1)*shift(2)+1  k2*shift(2) ];

    for p=1:3 % Fourier pyramid pair
      fi = FIndex{l}(k1,k2,p); % Filter index
      F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
      A = A + F{l}(:,:,:,fi); % Add to normalizing array
    end % p

    %%% 8. case
    % Here both X and Z dimensions are smaller so we can do that by removing
    % x = 1. This also reverts changes done in case 7.
    mRadial(1,:,:) = [];
    mRadial(1,:,:) = .5; % First (and last) Z-value
    mRadial(shift(1), :, shift(2)) = 1/3; % Last X value, last Z value
    k1 = numDir(1);
    k2 = numDir(2);
    %%%
    % Note how the shorter X and Z dimensions are taken into account!
    mRadialIdx=[(k1-1)*shift(1)+1  k1*shift(1) ;1 cubeSize ; (k2-1)*shift(2)+1  k2*shift(2) ];

    for p=1:3 % Fourier pyramid pair
      fi = FIndex{l}(k1,k2,p); % Filter index
      F{l}(:,:,:,fi) = PolarToRec(mRadialIdx,mRadial,cubeSize,P{p}); % Store filter
      A = A + F{l}(:,:,:,fi); % Add to normalizing array
    end % p

    %%%%%%%%
    % ALL CASES COMPLETE
    %%%%%%%%

    %%% Normalize all filters using A. Then inverse Fourier transform them to
    %%% the spatial domain.
    for fi = 1:length(FIndex{l}(:))
        tmpFilter = F{l}(:,:,:,fi) ./ A;
        % Q: What is the point of the outer fftshift?
        F{l}(:,:,:,fi) = squeeze(fftshift(ifftn(fftshift(tmpFilter),'symmetric')));
    end
    % (For some reason) the 1st and 2nd Fourier pyramids are switched around.
    % Here this is done simply by changing the index array.
    % (The numbering is anyways based on the output of GeneratePyramidSection)
    FIndex{l} = FIndex{l}(:,:,[2,1,3]);

end % level


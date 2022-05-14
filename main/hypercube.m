function C = hypercube(varargin)
%HYPERCUBE creates N-dimensional array of randomized cube-regions
%
% T. Heikkilä   2021

% Input is very flexible. First input gives the size of the hypercube.
if nargin < 1 % Default to 4D cube of size 16^4
    varargin{1} = [16 16 16 16];
end
% Otherwise use first input argument
SZ = varargin{1};

if nargin > 2
    error('Too many input arguments!')
elseif nargin > 1
    % Second input argument is the dimension
    dim = varargin{2};
    if ~isnumeric(dim) || dim <= 0 || rem(dim,1) ~= 0
        error('Dimension must be a positive integer')
    end
    if length(SZ) == 1
        SZ = SZ*ones(1,dim);
    elseif length(SZ) ~= dim
        error('Either specify the size for each dimension or give one value')
    end
elseif length(SZ) > 1
    % Only one input - > use length of the size vector
    dim = length(SZ);
else
    % If only one value - > default to 4D
    dim = 4;
    SZ = SZ*ones(1,dim);
end

if prod(SZ) > 1000000
    % For more than million elements use single precision
    dataClass = 'single';
else
    dataClass = 'double';
end

% Generate smaller array
M = 2*ones(1,dim);
for d = 1:dim
    if rem(SZ(d), 32) == 0 % Divisible by 32
        M(d) = 2.^(randi(4,1)); % Pick randomly from 2, 4, 8 and 16
        
    elseif rem(SZ(d), 20) == 0 % Divisible by 20
        opt = [20, 10, 5, 4];
        M(d) = opt(randi(length(opt), 1)); % Pick randomly from 20, 10 5 and 4
        
    elseif rem(SZ(d), 16) == 0 % Divisible by 16
        M(d) = 2.^(randi(3,1)); % Pick randomly from 2, 4 and 8
        
    elseif rem(SZ(d),12) == 0 % Divisible by 12
        M(d) = randi(3,1)+1; % Pick randomly from 2,3 and 4
        
    elseif rem(SZ(d),6) == 0 % Divisible by 6
        M(d) = randi(2,1)+1; % Pick randomly from 2 and 3
        
    elseif rem(SZ(d),4) == 0 % Divisible by 4
        M(d) = 2*randi(2,1); % Pick randomly from 2 and 4
        
    elseif rem(SZ(d),3) == 0 % Divisible by 3
        M(d) = 3;            % Pick 3
    else
        M(d) = randi(2,1)+1; % Pick randomly from 2 and 3
    end
end
sz = floor(SZ./M);

% random values between [0,1] but only 5 distinct values
smallCube = 0.2*(randi(6,sz,dataClass)-1);

% Create larger hypercube C
C = zeros(SZ,dataClass);

indCell = cell(1,dim);
for d = 1:dim
    ind = repmat(1:sz(d),[M(d),1]); % Repeat by the number of multiples
    ind = ind(:)'; % Row vector with each element M(dim) times
    
    while SZ(d) > length(ind) % Too short
        % We have to add a random index addition time to get correct length
        r = randi(length(ind),1); % Random index
        ind = [ind(1:r),ind(r:end)]; % ind(r) is now included again time
    end
    indCell{d} = ind;
end
C = smallCube(indCell{:});








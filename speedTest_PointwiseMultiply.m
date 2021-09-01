%%% Pointwise multiplication speed test
clear all
rng(0,'twister');
tic
n = 0;
szMax = 128;
TMax = 32;
dataClass = 'double';
while n < 500
    spatSz = randi(szMax,[1,3]);
    T = randi(TMax,1);
    
    X = randn([spatSz, T],dataClass);
    Y = randn(spatSz,dataClass);
 
%     Z = bsxfun(@times,X,Y);
%     Z = X .* Y;
    Z = X .* repmat(Y,[1 1 1 T]);
    
    n = n+1;
end
timeTaken = toc
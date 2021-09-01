function f = icylfft3(F)
%ICYLFFT3 is a cylindrical iFFT performed only on the first 3 dimensions
%   T H   2021
f = real(ifft(ifft(ifft(F,[],1),[],2),[],3));
end
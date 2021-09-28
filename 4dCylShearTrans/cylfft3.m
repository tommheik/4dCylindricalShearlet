function F = cylfft3(f)
%CYLFFT3 is a cylindrical FFT performed only on the first 3 dimensions
%   T H   2021
F = fft(fft(fft(f,[],1),[],2),[],3);
end
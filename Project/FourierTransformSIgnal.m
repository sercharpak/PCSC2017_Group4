clear all;
close all;
clc;

A = audioread('cmake-build-debug/wav_mono_16bit_44100.wav');

L = length(A);

n = 2^nextpow2(L);

Y = fft(A,n);

Fs = 44100;

f = Fs*(0:(n/2))/n;
P = abs(Y/n);

%plot(f,P(1:n/2+1)) 
grid on;

x = linspace(0,2*pi,1000);

plot(x,sin(2*pi*440*x));

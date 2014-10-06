%% Clean up
close all;
clear all;
clc;
format long;


%% Apply the metropolis algorithm
% ..while varying the variational parameters.
N      = 10^3;
n      = 13;
alpha  = linspace(0.8, 1.2, n);
energy = zeros(n, 1);

for i=1:n
    systemStr = sprintf('../VMC-Release/VMC %d %d %d %d', ...
                        N, alpha(i), alpha(i), 0)
    system(systemStr);
    data = load('data.dat');
    energy(i) = data(5);
end


%% Plot resulting energy
figure(1);
plot(alpha, energy);
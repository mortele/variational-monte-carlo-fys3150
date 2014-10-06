%% Clean up
close all;
clear all;
clc;
format long;


%% Apply the metropolis algorithm
% ..while varying the variational parameters.
N      = 5;
n      = 150;
m      = 50;
alpha  = linspace(0.5, 1.5, n);
energy = zeros(n, 1);

for i=1:n
    sprintf('Progress: %10.3f %%',100*i/n)
    energy(i) = 0;
    for j=1:m
        
        systemStr = sprintf('../VMC-Release/VMC %d %d %d %d', ...
                            N, alpha(i), alpha(i), 0);
        system(systemStr);
        data = load('data.dat');
        energy(i) = energy(i) + data(5);
    end
    energy(i) = energy(i) / m;
end


%% Plot resulting energy
figure(1);
plot(alpha, energy);
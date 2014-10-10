%% Clean up
close all;
clear all;
clc;
format long;


%% Apply the metropolis algorithm
% % ..while varying the variational parameters, NON-INTERACTING electrons.
% N      = 5;
% n      = 150;
% m      = 50;
% alpha  = linspace(0.5, 1.5, n);
% energy = zeros(n, 1);
% 
% for i=1:n
%     sprintf('Progress: %10.3f %%',100*i/n)
%     energy(i) = 0;
%     for j=1:m
%         
%         systemStr = sprintf('../VMC-Release/VMC %d %d %d %d', ...
%                             N, alpha(i), alpha(i), 0);
%         system(systemStr);
%         data = load('data.dat');
%         energy(i) = energy(i) + data(5);
%     end
%     energy(i) = energy(i) / m;
% end
% 
% 
% %% Plot resulting energy
% figure(1);
% plot(alpha, energy);


%% Apply the metropolis algorithm
% ..while varying the variational parameters, INTERACTING electrons.
N      = 5;
nAlpha = 12;
nBeta  = 12;
m      = 5;
alpha  = linspace(0.9, 1.1, nAlpha);
beta   = linspace(0.5, 0.6, nBeta);
energy = zeros(nAlpha, nBeta);

for i=1:nAlpha
    for j=1:nBeta   
        
        sprintf('Progress: %10.3f %%', 100*((i-1)*nAlpha + j)/(nAlpha*nBeta))
        
        energy(i,j) = 0;
        
        for k=1:m
            systemStr = sprintf('../VMC-Release/VMC %d %d %d %d %d', ...
                                N, alpha(i), beta(j), 0, 0);
            system(systemStr);
            data = load('data.dat');
            energy(i,j) = energy(i,j) + data(5);
        end
        energy(i,j) = energy(i,j) / m;
    end
end


%% Plot resulting energy
figure(1);
mesh(alpha, beta, energy');
xlabel('alpha');
ylabel('beta');
zlabel('energy');

[minAlpha, alphaIndex] = min(energy);
[minBeta,  betaIndex]  = min(minAlpha);

[a,b] = find(energy==min(energy(:)))



sprintf('min.energy=%8.15g, alpha=%10.5f, beta=%10.5f\n',...
         energy(a,b), alpha(a), beta(b))

k = 3;
figure(2);
mesh(alpha(a-k:a+k), beta(b-k:b+k), energy(a-k:a+k,b-k:b+k));
xlabel('alpha');
ylabel('beta');
zlabel('energy');




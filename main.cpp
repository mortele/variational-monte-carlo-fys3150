#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <armadillo>
#include <vector>

#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>
#include <Wavefunctions/TwoElectronInteracting.h>

#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/HarmonicOscillator.h>
#include <Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h>

#include <Math/RandomNumberGenerator.h>

#include <System.h>
#include <StatisticsSampler.h>

using namespace std;
using namespace arma;


int main(int argc, char* argv[]) {

    // Numerics.
    long   seed = 1001;
    double dx   = 0.05;
    int    N    = 5*pow(10,  5);
    int    M    = floor(N/4);
    const char*  fileName = "../VMC/data.dat";
    vec alpha = vec(2);
    alpha(0) = 0.85;
    alpha(1) = 0.5;

    if (argc > 1) {
        N = pow(10, atoi(argv[2]));
    }

    System             system;
    StatisticsSampler* statistics;

    system.setTrialWavefunction(new TwoElectronInteracting(alpha));
    system.setHamiltonian      (new HarmonicOscillatorWithCoulombInteraction);

    //system.setTrialWavefunction(new TwoElectronNonInteracting);
    //system.setHamiltonian      (new HarmonicOscillator);

    system.setRandomNumberGeneratorSeed(&seed);
    system.setUpMetropolis(N, M, dx);

    statistics = system.runMetropolisAlgorithm(true);

    statistics->printDataToTerminal();
    statistics->printDataToFile(fileName);

    // Program executed successfully, return 0.
    return 0;
}


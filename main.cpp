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

//FIXME: Variance is negative for alpha=1, two-electrons with no interaction. Should always
//       be positive.
//TODO:  Add functionality to statsSampler to record the positions for each metropolis step,
//       in order to plot one-body density.
//TODO:  Test with 3D HO-with-interactiong-hamiltonian and omega_r against M. Taut's values,
//       as in project 2.


    // Numerics.
    long         seed        = 1001;
    double       dx          = 2;
    double       omega       = 0.25;
    int          N           = 10 * pow(10, 5);
    int          M           = floor(N / 4);
    bool         printOutput = true;
    const char*  fileName    = "../VMC/data.dat";

    // Default alpha values.
    vec alpha = vec(2);
    alpha(0) = 0.9;
    alpha(1) = 0.2;

    if (argc > 1) {
        N           = pow(10, atoi(argv[2]));
        M           = floor(N / 4);
        alpha(0)    = atof(argv[3]);
        alpha(1)    = atof(argv[4]);
        printOutput = atoi(argv[5]);
    }

    System             system;
    StatisticsSampler* statistics;

    system.setTrialWavefunction(new TwoElectronInteracting(alpha));
    system.getWavefunction()->setNumberOfDimensions(3);
    system.setHamiltonian      (new HarmonicOscillatorWithCoulombInteraction(omega));

    //system.setTrialWavefunction(new TwoElectronNonInteracting(alpha));
    //system.setHamiltonian      (new HarmonicOscillator(omega));

    system.setRandomNumberGeneratorSeed(&seed);
    system.setUpMetropolis(N, M, dx);

    statistics = system.runMetropolisAlgorithm(printOutput);

    statistics->printDataToTerminal();
    statistics->printDataToFile(fileName);

    // Program executed successfully, return 0.
    return 0;
}


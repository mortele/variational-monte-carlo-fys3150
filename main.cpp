#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <time.h>
#include <sys/timeb.h>

#include <System.h>
#include <StatisticsSampler.h>
#include <timing.h>

#include <Math/RandomNumberGenerator.h>

#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>
#include <Wavefunctions/TwoElectronInteracting.h>

#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/HeliumAtom.h>
#include <Hamiltonians/HarmonicOscillator.h>
#include <Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h>

using std::cout;
using std::endl;
using std::atof;
using std::atoi;
using arma::vec;

typedef unsigned long long int ullint;
typedef               long int   lint;

///////////////////////////////////////////////////////////////////////////
// TODO:  Test with 3D HO-with-interactiong-hamiltonian and omega_r against
//        M. Taut's values, as in project 2.
// TODO:  Parallelize with MPI? OMP?
// TODO:  Run test against known results for He atom.
// FIXME: Removing the virtual from Hamiltonian::evaluateLocalEnergy(R)
//        gives balle results. Fix?
///////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]) {

    // Use the current time (since the start of the UNIX epoch, 1 January
    // 1970) (in microseconds) as a seed for the random number generator.
    ullint startTime = unixTimeInMicroseconds();
    lint   maxValueSignedLongInt = pow(2,31)-2;

    // Numerical and physical parameters.
    int    testCase     = 2;
    lint   seed         = (lint) (startTime % maxValueSignedLongInt);
    int    N            = pow(10, 5);
    int    M            = floor(N / 4);
    double dx           = 10.0;
    double omega        = 0.25;
    bool   printOutput  = true;
    bool   storeOneBody = false;
    const char*  fileName = "../VMC/data.dat";

    // Variational parameters.
    vec alpha = vec(2);

    // Check if parameters are given as command line arguments.
    if (argc > 1) {
        N            = pow(10, atoi(argv[1]));
        M            = floor(N / 4);
        alpha(0)     = atof(argv[2]);
        alpha(1)     = atof(argv[3]);
        printOutput  = atoi(argv[4]);
        storeOneBody = atoi(argv[5]);
    }

    System             system;
    StatisticsSampler* statistics;

    switch (testCase) {
        case 0: {
            dx = 2; omega = 1;
            alpha(0) = 1;
            system.setTrialWavefunction(new TwoElectronNonInteracting(alpha));
            system.setHamiltonian      (new HarmonicOscillator(omega));
            break;
        } case 1: {
            dx = 10; omega = 0.25;
            alpha(0) = 0.61076;
            alpha(1) = 0.78987;
            system.setTrialWavefunction(new TwoElectronInteracting(alpha));
            system.setNumberOfDimensions(3);
            system.setHamiltonian(new HarmonicOscillatorWithCoulombInteraction(omega));
            break;
        } case 2: {
            dx = 1.5; omega = 1;
            alpha(0) = 1.843;
            alpha(1) = 0.347;
            system.setTrialWavefunction(new TwoElectronInteracting(alpha));
            system.setNumberOfDimensions(3);
            system.setHamiltonian(new HeliumAtom);

            break;
        } default: {
            break;
        }
    }

    system.setRandomNumberGeneratorSeed(&seed);
    system.setUpMetropolis(N, M, dx, storeOneBody);

    statistics = system.runMetropolisAlgorithm(printOutput);

    statistics->printDataToFile(fileName);
    if (printOutput) statistics->printDataToTerminal(unixTimeInMicroseconds() -
                                                     startTime);

    // Program executed successfully, return 0.
    return 0;
}


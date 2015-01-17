#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <cstdlib>
#include <armadillo>
#include <time.h>
#include <sys/timeb.h>

//#include <System.h>
//#include <StatisticsSampler.h>
#include <timing.h>

#include <Math/RandomNumberGenerator.h>

#include <Wavefunctions/WaveFunction.h>
#include <Wavefunctions/Slater.h>

#include <Hamiltonians/Hamiltonian.h>

using std::cout;
using std::endl;
using std::atof;
using std::atoi;
using arma::vec;

typedef unsigned long long int ullint;
typedef               long int   lint;


int main() {

    // Use the current time (since the start of the UNIX epoch, 1 January
    // 1970) (in microseconds) as a seed for the random number generator.
    ullint startTime = unixTimeInMicroseconds();
    lint   maxValueSignedLongInt = pow(2,31)-2;

    // Numerical and physical parameters.
    int    testCase     = 1;
    lint   seed         = (lint) (startTime % maxValueSignedLongInt);
    int    N            = pow(10, 7);
    int    M            = floor(N / 4);
    double dx           = 10.0;
    double omega        = 0.25;
    bool   printOutput  = true;
    bool   storeOneBody = false;
    const char*  fileName = "../VMC/data.dat";

    // Variational parameters.
    vec alpha = vec(2);

    //System             system;
    //StatisticsSampler* statistics;

//            // Two NON-INTERACTING electrons in an external harmonic oscillator well.
//            dx = 1.5; omega = 1.0;
//            alpha(0) = 1.0;
//            system.setTrialWavefunction(new TwoElectronNonInteracting(alpha));
//            system.setHamiltonian      (new HarmonicOscillator(omega));
//            break;


    Slater hei(1,1);


    /*system.setRandomNumberGeneratorSeed(&seed);
    system.setUpMetropolis(N, M, dx, storeOneBody);

    statistics = system.runMetropolisAlgorithm(printOutput);

    statistics->printDataToFile(fileName);
    if (printOutput) statistics->printDataToTerminal(unixTimeInMicroseconds() -
                                                     startTime);
    */

    // Program executed successfully, return 0.
    return 0;
}


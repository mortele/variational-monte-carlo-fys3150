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
#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>
#include <Wavefunctions/TwoElectronInteracting.h>
#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/HarmonicOscillator.h>
#include <Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h>
#include <Math/RandomNumberGenerator.h>



using namespace std;
using namespace arma;


int main(int argc, char* argv[]) {

//FIXME: Variance is negative for alpha=1, two-electrons with no interaction. Should always
//       be positive.
//TODO:  Add functionality to statsSampler to record the positions for each metropolis step,
//       in order to plot one-body density.
//TODO:  Test with 3D HO-with-interactiong-hamiltonian and omega_r against M. Taut's values,
//       as in project 2. Also figure out if it actually makes any sense to perform this
//       test(?).
//TODO:  Put most of the evaluateLocalEnergy method in the superclass? As it is now, a lot
//       of code is identical between HOwithCoulombInteraction and HO.
//TODO:  Parallelize with MPI? OMP?
//TODO:  Clean up include statements in .h and .cpp files. Move anything that can be moved
//       to .cpp files to speed up compilation time.


    // Use the current time (since the start of the UNIX epoch, 1 January 1970) (in
    // milliseconds) as a seed for the random number generator.
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    unsigned long long unixTimeInMilliSeconds = (unsigned long long)ts.tv_sec  * 1000000LL +
                                                (unsigned long long)ts.tv_nsec / 1000LL;
    long int maxValueSignedLongInt = 2147483647;

    // Numerics.
    long int     seed        = (long int) (unixTimeInMilliSeconds % maxValueSignedLongInt);
    int          N           = pow(10, 6);
    int          M           = floor(N / 4);
    double       dx          = 10.0;
    double       omega       = 0.25;
    bool         printOutput = true;
    const char*  fileName    = "../VMC/data.dat";

    // Default alpha values.
    vec alpha = vec(2);
    alpha(0) = 0.62102;
    alpha(1) = 0.72286;

    // Check if parameters are given as command line arguments.
    if (argc > 1) {
        N           = pow(10, atoi(argv[1]));
        M           = floor(N / 4);
        alpha(0)    = atof(argv[2]);
        alpha(1)    = atof(argv[3]);
        printOutput = atoi(argv[4]);
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

    if (printOutput) statistics->printDataToTerminal();
    statistics->printDataToFile(fileName);

    // Program executed successfully, return 0.
    return 0;
}


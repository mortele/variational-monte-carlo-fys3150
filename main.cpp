#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <armadillo>

#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>

#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/HarmonicOscillator.h>

#include <System.h>

using namespace std;
using namespace arma;


int main(int argc, char* argv[]) {


    System system;

    system.setTrialWavefunction(new TwoElectronNonInteracting());
    system.setHamiltonian      (new HarmonicOscillator());



    return 0;



    TwoElectronNonInteracting trial;
    HarmonicOscillator H(&trial);

    mat R     = randu<mat>(2,2);
    vec alpha = ones<vec>(2);

    alpha(0) = 1;
    alpha(1) = 1000;


    int N = pow(10,5);
    int M = floor(N/5);

    double stepSize = 0.0005;
    double energy = 0;

    trial.setOldWaveFunctionSquared(trial.evaluateWavefunction(alpha,R) *
                                    trial.evaluateWavefunction(alpha, R));


    srand (1);
    int accepted = 0;

    for (int step = 0; step < N; step++) {
        mat Rnew = R;
        int randomParticle   = rand() % 2;
        int randomCoordinate = rand() % 2;
        double randomStep    = (((double) rand() / (double) RAND_MAX)*2-1) * stepSize;

        Rnew(randomParticle, randomCoordinate) += randomStep;
        double newWavefunctionSquared = pow(trial.evaluateWavefunction(alpha, Rnew), 2);
        double oldWavefunctionSquared = trial.getOldWaveFunctionSquared();

        if (newWavefunctionSquared > oldWavefunctionSquared) {
            R = Rnew;
            trial.setOldWaveFunctionSquared(newWavefunctionSquared);
            if (step >= M) accepted++;
        } else {
            double acceptanceRatio = (double) rand() / (double) RAND_MAX; // uniform random, (0,1]
            if (acceptanceRatio > newWavefunctionSquared / oldWavefunctionSquared) {
                R = Rnew;
                trial.setOldWaveFunctionSquared(newWavefunctionSquared);
                if (step >= M) accepted++;
            }
        }

        printf("Progress: %10.2f \% \r", 100.0*step/(double)N);
        fflush(stdout);

        if (step >= M) {
            energy += H.evaluateLocalEnergy(alpha, R);
        }
    }

    printf("=========================================\n");
    printf("================finished!================\n");
    printf("=========================================\n");
    printf("Energy                  = %15.6f\n",   energy / ((double) (N-M)));
    printf("Ratio of accepted steps = %15.6f\n\n", accepted / ((double) (N-M)));

    // Program run successfully.
    return 0;
}


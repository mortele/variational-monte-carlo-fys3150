#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <armadillo>

#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>

#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/NonInteractingHamiltonian.h>


using namespace std;
using namespace arma;



int main(int argc, char* argv[]) {

    TwoElectronNonInteracting trial;
    NonInteractingHamiltonian H(&trial);

    mat R     = randu<mat>(2,2);
    vec alpha = ones<vec>(2);

    double hei = trial.evaluateWavefunctionSquared(alpha, R);

    //double ja = localEnergy(trial.evaluateWavefunctionSquared, alpha, R);
    cout << "hei" << endl;


    // Program run successfully.
    return 0;
}


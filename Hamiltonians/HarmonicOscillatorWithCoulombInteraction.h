#pragma once
#include <armadillo>
#include <Hamiltonians/Hamiltonian.h>

using arma::mat;

class TrialWavefunction;

class HarmonicOscillatorWithCoulombInteraction : public Hamiltonian {

public:
    HarmonicOscillatorWithCoulombInteraction();
    HarmonicOscillatorWithCoulombInteraction(double omega);
    HarmonicOscillatorWithCoulombInteraction(TrialWavefunction* trial);
    ~HarmonicOscillatorWithCoulombInteraction() {}
    void setTrialWavefunction(TrialWavefunction* trial);
    double evaluateLocalEnergy(mat R);
};

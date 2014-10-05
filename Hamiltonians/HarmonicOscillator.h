#pragma once
#include <armadillo>

#include <Hamiltonians/Hamiltonian.h>

#include <Wavefunctions/TrialWavefunction.h>


class HarmonicOscillator : public Hamiltonian {

public:
    HarmonicOscillator();
    HarmonicOscillator(TrialWavefunction* trial);
    ~HarmonicOscillator() {}
    void setTrialWavefunction(TrialWavefunction* trial);
    double evaluateLocalEnergy(arma::mat R);
};


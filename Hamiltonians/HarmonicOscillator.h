#pragma once
#include <armadillo>

#include <Hamiltonians/Hamiltonian.h>

#include <Wavefunctions/TrialWavefunction.h>


class HarmonicOscillator : public Hamiltonian {
private:
    TrialWavefunction* m_waveFunction;

public:
    HarmonicOscillator();
    HarmonicOscillator(TrialWavefunction* trial);
    ~HarmonicOscillator() {}
    void setTrialWavefunction(TrialWavefunction* trial);
    double evaluateLocalEnergy(arma::vec a, arma::mat R);
};


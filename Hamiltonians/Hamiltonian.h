#pragma once
#include <armadillo>

#include <Wavefunctions/TrialWavefunction.h>

class Hamiltonian {
private:
    TrialWavefunction *m_waveFunction;

public:
    Hamiltonian();
    ~Hamiltonian() {}
    virtual double evaluateLocalEnergy(arma::vec a, arma::mat R) = 0;
};

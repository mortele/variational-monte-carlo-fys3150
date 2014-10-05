#pragma once
#include <armadillo>

#include <Wavefunctions/TrialWavefunction.h>

class Hamiltonian {
private:
    TrialWavefunction *m_waveFunction;

public:
    Hamiltonian() {}
    ~Hamiltonian() {}
    virtual void   setTrialWavefunction(TrialWavefunction* trial) = 0;
    virtual double evaluateLocalEnergy (arma::vec a, arma::mat R) = 0;
};

#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>


class Hamiltonian {

protected:
    TrialWavefunction *m_wavefunction;

public:
    Hamiltonian() {}
    ~Hamiltonian() {}
    virtual void   setTrialWavefunction(TrialWavefunction* trial);
    virtual double evaluateLocalEnergy (arma::mat R);
};

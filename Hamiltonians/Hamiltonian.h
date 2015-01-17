#pragma once
#include <armadillo>
#include <Wavefunctions/WaveFunction.h>


class Hamiltonian {

protected:
    WaveFunction *m_wavefunction;

public:
    Hamiltonian() {}
    ~Hamiltonian() {}

    virtual void   setTrialWavefunction(WaveFunction* trial) = 0;
    virtual double evaluateLocalEnergy (arma::mat R);
};

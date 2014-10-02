#pragma once
#include <armadillo>


class TrialWavefunction;

class Hamiltonian {
private:
    TrialWavefunction *m_waveFunction;

public:
    Hamiltonian();
    ~Hamiltonian() {}
    virtual double evaluateLocalEnergy(arma::vec a, arma::mat R) = 0;
};

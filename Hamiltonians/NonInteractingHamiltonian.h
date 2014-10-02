#pragma once
#include <Hamiltonians/Hamiltonian.h>
#include <armadillo>

class TrialWavefunction;

class NonInteractingHamiltonian : public Hamiltonian {
private:
    TrialWavefunction* m_waveFunction;

public:
    NonInteractingHamiltonian(TrialWavefunction* trial);
    ~NonInteractingHamiltonian() {}
    double evaluateLocalEnergy(arma::vec a, arma::mat R);
};


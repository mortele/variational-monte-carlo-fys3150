#pragma once
#include <armadillo>

#include <Hamiltonians/Hamiltonian.h>

#include <Wavefunctions/TrialWavefunction.h>


class NonInteractingHamiltonian : public Hamiltonian {
private:
    TrialWavefunction* m_waveFunction;

public:
    NonInteractingHamiltonian(TrialWavefunction* trial);
    ~NonInteractingHamiltonian() {}
    double evaluateLocalEnergy(arma::vec a, arma::mat R);
};


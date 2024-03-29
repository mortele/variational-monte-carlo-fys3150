#pragma once
#include <armadillo>
#include <Hamiltonians/Hamiltonian.h>


class HeliumAtom : public Hamiltonian {

public:
    HeliumAtom() {}
    ~HeliumAtom() {}

    void   setTrialWavefunction(TrialWavefunction *trial);
    double evaluateLocalEnergy(arma::mat R);
};



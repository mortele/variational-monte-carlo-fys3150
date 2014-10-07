#pragma once
#include <armadillo>
#include <Hamiltonians/Hamiltonian.h>


class HeliumAtom : public Hamiltonian {

public:
    HeliumAtom() {}
    ~HeliumAtom() {}

    double evaluateLocalEnergy(arma::mat R);
};



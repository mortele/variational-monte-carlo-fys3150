#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>


class HeliumAtomWavefunction : public TrialWavefunction {

public:
    HeliumAtomWavefunction(arma::vec a);
    ~HeliumAtomWavefunction() {}

    double evaluateWavefunction(arma::mat R);
    arma::mat setInitialPosition();
};

#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>

using arma::mat;
using arma::vec;


class TwoElectronNonInteracting : public TrialWavefunction {

public:
    TwoElectronNonInteracting();
    TwoElectronNonInteracting(vec a);
    ~TwoElectronNonInteracting() {}

    double evaluateWavefunction(mat R);
    mat    setInitialPosition();
};

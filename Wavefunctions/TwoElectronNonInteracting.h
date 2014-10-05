#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>

using arma::mat;
using arma::vec;


class TwoElectronNonInteracting : public TrialWavefunction {

public:
    TwoElectronNonInteracting() {m_alpha = vec(1); m_alpha(0) = 1;}
    ~TwoElectronNonInteracting() {}

    double evaluateWavefunction(mat R);
    mat    setInitialPosition();
};

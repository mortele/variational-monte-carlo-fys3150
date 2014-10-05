#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>


class TwoElectronInteracting : public TrialWavefunction {

public:
    TwoElectronInteracting() {m_alpha = arma::vec(2); m_alpha(0) = 0.9; m_alpha(1) = 0.2;}
    ~TwoElectronInteracting() {}

    double evaluateWavefunction(arma::mat R);
    mat    setInitialPosition();
};

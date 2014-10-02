#pragma once
#include <armadillo>
#include <complex>
#include <cmath>

#include <Wavefunctions/TrialWavefunction.h>


class TwoElectronNonInteracting : public TrialWavefunction {
private:
    double m_oldWaveFunctionSquaredValue;

public:
    TwoElectronNonInteracting() {}
    ~TwoElectronNonInteracting() {}

    double evaluateWavefunctionSquared(arma::vec alpha, arma::mat R);
};
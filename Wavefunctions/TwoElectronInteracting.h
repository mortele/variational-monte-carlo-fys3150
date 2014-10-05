#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>

class TrialWavefunction;


class TwoElectronInteracting : public TrialWavefunction {

public:
    TwoElectronInteracting();
    ~TwoElectronInteracting() {}

    double evaluateWavefunction(arma::mat R);
    mat    setInitialPosition();
};

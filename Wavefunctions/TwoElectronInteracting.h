#pragma once
#include <armadillo>
#include <Wavefunctions/TrialWavefunction.h>

class TrialWavefunction;


class TwoElectronInteracting : public TrialWavefunction {

public:
    TwoElectronInteracting();
    TwoElectronInteracting(arma::vec a);
    ~TwoElectronInteracting() {}

    double evaluateWavefunction(arma::mat R);
    mat    setInitialPosition();
};

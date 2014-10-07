#pragma once
#include <armadillo>
#include <Wavefunctions/TwoElectronNonInteracting.h>


class TwoElectronInteracting : public TwoElectronNonInteracting {

public:
    TwoElectronInteracting(arma::vec a);
    ~TwoElectronInteracting() {}

    double evaluateWavefunction(arma::mat R);
};

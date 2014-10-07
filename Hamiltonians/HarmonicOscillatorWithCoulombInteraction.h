#pragma once
#include <armadillo>
#include <Hamiltonians/HarmonicOscillator.h>


class TrialWavefunction;

class HarmonicOscillatorWithCoulombInteraction : public HarmonicOscillator {

public:
    HarmonicOscillatorWithCoulombInteraction(double omega);
    ~HarmonicOscillatorWithCoulombInteraction() {}

    double evaluateLocalEnergy(arma::mat R);
};

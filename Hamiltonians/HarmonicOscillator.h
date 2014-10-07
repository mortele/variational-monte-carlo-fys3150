#pragma once
#include <Hamiltonians/Hamiltonian.h>
#include <armadillo>


class TrialWavefunction;


class HarmonicOscillator : public Hamiltonian {

protected:
    double m_omega;

public:
    HarmonicOscillator() {}
    HarmonicOscillator(double omega) {m_omega = omega;}
    ~HarmonicOscillator() {}

    void setTrialWavefunction(TrialWavefunction* trial);
    double evaluateLocalEnergy(arma::mat R);
};

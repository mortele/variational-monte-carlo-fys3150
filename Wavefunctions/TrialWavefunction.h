#pragma once
#include <armadillo>


class TrialWavefunction {
private:
    double m_oldWaveFunctionSquaredValue;

public:
    TrialWavefunction();
    virtual ~TrialWavefunction() {}
    virtual double evaluateWavefunction(arma::vec, arma::mat) = 0;

    double getOldWaveFunctionSquared() {return m_oldWaveFunctionSquaredValue;}
    void setOldWaveFunctionSquared(double old) {m_oldWaveFunctionSquaredValue = old;}
};

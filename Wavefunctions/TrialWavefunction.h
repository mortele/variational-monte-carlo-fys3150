#pragma once
#include <armadillo>

using arma::vec;
using arma::mat;


class TrialWavefunction {
protected:
    vec    m_alpha;
    double m_oldWaveFunctionSquaredValue;
    long*  m_seed;

public:
    TrialWavefunction();
    virtual ~TrialWavefunction() {}
    virtual double evaluateWavefunction(mat) = 0;
    virtual mat    setInitialPosition()      = 0;

    // Getters, setters.
    double getOldWaveFunctionSquared()              {return m_oldWaveFunctionSquaredValue;}
    void   setOldWaveFunctionSquared(double old)    {m_oldWaveFunctionSquaredValue = old;}
    void   setAlpha(vec a)                          {m_alpha = a;}
    void   setRandomNumberGeneratorSeed(long* seed) {m_seed = seed;}
    vec    getAlpha()                               {return m_alpha;}
};

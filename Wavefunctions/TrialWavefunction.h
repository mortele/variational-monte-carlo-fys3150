#pragma once
#include <armadillo>

using arma::vec;
using arma::mat;


class TrialWavefunction {
protected:
    int    m_particles;
    int    m_dimensions;
    vec    m_alpha;
    double m_omega;
    double m_oldWaveFunctionSquaredValue;
    long*  m_seed;

public:
    TrialWavefunction();
    TrialWavefunction(vec a);
    virtual ~TrialWavefunction() {}
    virtual double evaluateWavefunction(mat) = 0;
    virtual mat    setInitialPosition()      = 0;

    // Getters, setters.
    double getOldWaveFunctionSquared()              {return m_oldWaveFunctionSquaredValue;}
    void   setOldWaveFunctionSquared(double old)    {m_oldWaveFunctionSquaredValue = old;}
    void   setAlpha(vec a)                          {m_alpha = a;}
    void   setRandomNumberGeneratorSeed(long* seed) {m_seed = seed;}
    void   setOmega(double omega)                   {m_omega = omega;}
    void   setNumberOfDimensions(int dimensions)    {m_dimensions = dimensions;}
    vec    getAlpha()                               {return m_alpha;}
    int    getNumberOfDimensions()                  {return m_dimensions;}
    int    getNumberOfParticles()                   {return m_particles;}
};

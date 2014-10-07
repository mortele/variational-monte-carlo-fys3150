#pragma once
#include <armadillo>


class TrialWavefunction {

protected:
    int    m_particles;
    int    m_dimensions;
    double m_omega;
    double m_oldWaveFunctionSquaredValue;
    long*  m_seed;
    arma::vec m_alpha;

public:
    TrialWavefunction() : m_oldWaveFunctionSquaredValue(0) {}
    TrialWavefunction(arma::vec a);
    ~TrialWavefunction() {}

    virtual double    evaluateWavefunction(arma::mat) = 0;
    virtual arma::mat setInitialPosition()            = 0;

    // Getters, setters.
    double getOldWaveFunctionSquared()           {return m_oldWaveFunctionSquaredValue;}
    void   setOldWaveFunctionSquared(double old) {m_oldWaveFunctionSquaredValue = old;}
    void   setAlpha(arma::vec a)                    {m_alpha = a;}
    void   setRandomNumberGeneratorSeed(long* seed) {m_seed = seed;}
    void   setOmega(double omega)                   {m_omega = omega;}
    void   setNumberOfDimensions(int dimensions)    {m_dimensions = dimensions;}
    int    getNumberOfDimensions()                  {return m_dimensions;}
    int    getNumberOfParticles()                   {return m_particles;}
    arma::vec getAlpha()                            {return m_alpha;}
};

#pragma once
#include <armadillo>


class Hamiltonian;
class WaveFunction;
class StatisticsSampler;


class System {

    friend class StatisticsSampler;

private:
    int    m_N;
    int    m_M;
    int    m_particles;
    int    m_dimensions;
    double m_dx;
    double m_executionTime;
    long*  m_seed;
    arma::mat          m_R;
    Hamiltonian       *m_hamiltonian;
    WaveFunction      *m_wavefunction;
    StatisticsSampler *m_statisticsSampler;

public:

    System();
    ~System() {};

    void               setUpMetropolis(int N, int M, double dx, bool storeOneBody);
    bool               metropolisStep();
    StatisticsSampler* runMetropolisAlgorithm(bool printProgress);

    // Getters, setters.
    void setRandomNumberGeneratorSeed(long*              seed);
    void setNumberOfDimensions       (int                numberOfDimensions);
    void setTrialWavefunction        (WaveFunction* trial);
    void setHamiltonian              (Hamiltonian*       hamiltonian);
    void setAlpha                    (arma::vec          a);
    WaveFunction* getWavefunction() {return m_wavefunction;}
};

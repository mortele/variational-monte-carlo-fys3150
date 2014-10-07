#pragma once
#include <armadillo>
#include <iostream>
#include <cmath>
#include <typeinfo>

class Hamiltonian;
class TrialWavefunction;

using arma::mat;
using arma::vec;
using arma::zeros;
using std::cout;
using std::endl;

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
    mat    m_R;
    long*  m_seed;

    Hamiltonian       *m_hamiltonian;
    TrialWavefunction *m_wavefunction;
    StatisticsSampler *m_statisticsSampler;

    void printPreInformation();

public:

    System();
    ~System();

    void               setUpMetropolis(int N, int M, double dx, bool storeOneBody);
    bool               metropolisStep();
    StatisticsSampler* runMetropolisAlgorithm(bool printProgress);

    // Getters, setters.
    void setRandomNumberGeneratorSeed(long*              seed);
    void setNumberOfDimensions       (int numberOfDimensions);
    void setTrialWavefunction        (TrialWavefunction* trial);
    void setHamiltonian              (Hamiltonian*       hamiltonian);
    void setAlpha                    (vec                a);
    TrialWavefunction* getWavefunction() {return m_wavefunction;}
};

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
    mat    m_R;
    long*  m_seed;

    TrialWavefunction *m_wavefunction;
    Hamiltonian       *m_hamiltonian;
    StatisticsSampler *m_statisticsSampler;

    void printPreInformation();

public:

    System();
    ~System();

    void               setUpMetropolis(int N, int M, double dx);
    bool               metropolisStep();
    StatisticsSampler* runMetropolisAlgorithm(bool printProgress);

    // Getters, setters.
    void setRandomNumberGeneratorSeed(long*              seed);
    void setTrialWavefunction        (TrialWavefunction* trial);
    void setHamiltonian              (Hamiltonian*       hamiltonian);
    void setAlpha                    (vec                a);
    TrialWavefunction* getWavefunction() {return m_wavefunction;}
};

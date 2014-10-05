#pragma once
#include <armadillo>

class Hamiltonian;
class TrialWavefunction;

using arma::mat;
using arma::vec;


class System {
private:
    int    m_N;
    int    m_M;
    double m_dx;
    mat    m_R;
    long*  m_seed;

    TrialWavefunction *m_wavefunction;
    Hamiltonian       *m_hamiltonian;

public:
    System();
    ~System();

    void setUpMetropolis(int N, int M, double dx);
    void runMetropolisAlgorithm();

    // Getters, setters.
    void setRandomNumberGeneratorSeed(long*              seed);
    void setTrialWavefunction        (TrialWavefunction* trial);
    void setHamiltonian              (Hamiltonian*       hamiltonian);
    void setAlpha                    (vec                a);
};

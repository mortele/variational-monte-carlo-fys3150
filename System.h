#pragma once
#include <armadillo>

class Hamiltonian;
class TrialWavefunction;


class System {
private:
    TrialWavefunction *m_wavefunction;
    Hamiltonian       *m_hamiltonian;

public:
    System();
    ~System();
    void setTrialWavefunction(TrialWavefunction* trial);
    void setHamiltonian(Hamiltonian* hamiltonian);
};

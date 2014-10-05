#include <System.h>
#include <Hamiltonians/Hamiltonian.h>
#include <Wavefunctions/TrialWavefunction.h>


System::System() {
}


System::~System() {
}


void System::setTrialWavefunction(TrialWavefunction *trial) {
    m_wavefunction = trial;
}


void System::setHamiltonian(Hamiltonian *hamiltonian) {
    m_hamiltonian = hamiltonian;
    m_hamiltonian->setTrialWavefunction(m_wavefunction);

}


void System::setAlpha(vec a) {
    m_wavefunction->setAlpha(a);
}


void System::setUpMetropolis(int N, int M, double dx) {
    m_N  = N;
    m_M  = M;
    m_dx = dx;

    m_R = m_wavefunction->setInitialPosition();
}


void System::setRandomNumberGeneratorSeed(long *seed) {
    m_wavefunction->setRandomNumberGeneratorSeed(seed);
}


void System::runMetropolisAlgorithm() {

}

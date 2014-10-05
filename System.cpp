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

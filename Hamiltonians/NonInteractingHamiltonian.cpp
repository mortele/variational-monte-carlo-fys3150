#include <Hamiltonians/NonInteractingHamiltonian.h>

NonInteractingHamiltonian::NonInteractingHamiltonian(TrialWavefunction* trial) {
    m_waveFunction = trial;
}


double NonInteractingHamiltonian::evaluateLocalEnergy(arma::vec a, arma::mat R) {

}



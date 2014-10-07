#include <Hamiltonians/HarmonicOscillator.h>
#include <Wavefunctions/TrialWavefunction.h>


using arma::vec;


void HarmonicOscillator::setTrialWavefunction(TrialWavefunction *trial){
    m_wavefunction = trial;
    m_wavefunction->setOmega(m_omega);
}


double HarmonicOscillator::evaluateLocalEnergy(arma::mat R) {

    int numberOfParticles  = m_wavefunction->getNumberOfParticles();

    // Compute the local kinetic energy.
    double kinetic = Hamiltonian::evaluateLocalEnergy(R);

    // Compute the local potential energy.
    double potential = 0;

    for (int particle = 0; particle < numberOfParticles; particle++) {
        vec    position  = R.row(particle).t();
        double rSquared  = dot(position, position);
        potential       += m_omega * m_omega * rSquared;
    }
    potential /= 2;

    return kinetic + potential;
}






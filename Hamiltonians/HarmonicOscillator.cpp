#include <Hamiltonians/HarmonicOscillator.h>

using std::cout;
using std::endl;
using arma::mat;
using arma::vec;
using arma::zeros;

HarmonicOscillator::HarmonicOscillator() {
}


HarmonicOscillator::HarmonicOscillator(double omega) {
    m_omega = omega;
}


HarmonicOscillator::HarmonicOscillator(TrialWavefunction* trial) {
    m_wavefunction = trial;
}


double HarmonicOscillator::evaluateLocalEnergy(arma::mat R) {

    int numberOfParticles  = m_wavefunction->getNumberOfParticles();
    int numberOfDimensions = m_wavefunction->getNumberOfDimensions();

    // Compute the local kinetic energy.
    mat    H       = zeros<mat>(numberOfParticles, numberOfDimensions);
    double h       = 1e-4;
    double kinetic = 0;

    for (int particle = 0; particle < numberOfParticles; particle++) {
        for (int coordinate = 0; coordinate < numberOfDimensions; coordinate++) {

            H(particle, coordinate) = h;
            kinetic -= (m_wavefunction->evaluateWavefunction(R+H) - 2 *
                        m_wavefunction->evaluateWavefunction(R)   +
                        m_wavefunction->evaluateWavefunction(R-H)) / (h*h);
            H(particle, coordinate) = 0;
        }
    }
    kinetic /= (2 * m_wavefunction->evaluateWavefunction(R));

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


void HarmonicOscillator::setTrialWavefunction(TrialWavefunction *trial){
    m_wavefunction = trial;
    m_wavefunction->setOmega(m_omega);
}






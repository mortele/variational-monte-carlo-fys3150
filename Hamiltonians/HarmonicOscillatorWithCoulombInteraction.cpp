#include <Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h>
#include <Hamiltonians/HarmonicOscillator.h>

using arma::mat;
using arma::vec;
using arma::zeros;
using arma::norm;

HarmonicOscillatorWithCoulombInteraction::HarmonicOscillatorWithCoulombInteraction() {
}


HarmonicOscillatorWithCoulombInteraction::HarmonicOscillatorWithCoulombInteraction(double omega) {
    m_omega = omega;
}


HarmonicOscillatorWithCoulombInteraction::HarmonicOscillatorWithCoulombInteraction(TrialWavefunction* trial) {
    m_wavefunction = trial;
}


double HarmonicOscillatorWithCoulombInteraction::evaluateLocalEnergy(arma::mat R) {

    int numberOfParticles  = m_wavefunction->getNumberOfParticles();
    int numberOfDimensions = m_wavefunction->getNumberOfDimensions();

    // Compute the local kinetic energy.
    mat    H       = zeros<mat>(numberOfParticles, numberOfDimensions);
    double h       = 1e-5;
    double kinetic = 0;

    for (int particle = 0; particle < numberOfParticles; particle++) {
        for (int coordinate = 0; coordinate < numberOfDimensions; coordinate++) {

            H(particle, coordinate) = h;
            kinetic -= (m_wavefunction->evaluateWavefunction(R+H)  - 2 *
                        m_wavefunction->evaluateWavefunction(R)    +
                        m_wavefunction->evaluateWavefunction(R-H)) / (h*h);
            H(particle, coordinate) = 0;

        }
    }
    kinetic /= (2 * m_wavefunction->evaluateWavefunction(R));

    // Compute the local potential energy.
    double    potential = 0;

    for (int particle = 0; particle < numberOfParticles; particle++) {
        vec    position  = R.row(particle).t();
        double rSquared  = dot(position, position);
        potential       += m_omega * m_omega * rSquared / 2.0;
    }
    for (int particle_i = 0; particle_i < numberOfParticles; particle_i++) {
        for (int particle_j = particle_i+1; particle_j < numberOfParticles; particle_j++) {
            vec r_ij        = R.row(particle_j).t() - R.row(particle_i).t();
            potential      += 1 / norm(r_ij);
        }
    }
    return kinetic + potential;
}


void HarmonicOscillatorWithCoulombInteraction::setTrialWavefunction(TrialWavefunction *trial){
    m_wavefunction = trial;
    m_wavefunction->setOmega(m_omega);
}





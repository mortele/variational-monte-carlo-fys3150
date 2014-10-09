#include <Hamiltonians/Hamiltonian.h>

using arma::mat;
using arma::zeros;


double Hamiltonian::evaluateLocalEnergy(arma::mat R) {

    int numberOfParticles  = m_wavefunction->getNumberOfParticles();
    int numberOfDimensions = m_wavefunction->getNumberOfDimensions();

    // Compute the local kinetic energy.
    mat    H       = zeros<mat>(numberOfParticles, numberOfDimensions);
    double h       = 1e-5;
    double kinetic = 0;

    for (int particle = 0; particle < numberOfParticles; particle++) {
        for (int coordinate = 0; coordinate < numberOfDimensions; coordinate++) {

            H(particle, coordinate) = h;
            kinetic -= (m_wavefunction->evaluateWavefunction(R+H)   -
                        2 * m_wavefunction->evaluateWavefunction(R) +
                        m_wavefunction->evaluateWavefunction(R-H))  / (h*h);
            H(particle, coordinate) = 0;
        }
    }
    kinetic /= (2 * m_wavefunction->evaluateWavefunction(R));
    return kinetic;
}




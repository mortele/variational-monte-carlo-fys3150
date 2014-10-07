#include <Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h>
#include <Hamiltonians/HarmonicOscillator.h>

using arma::mat;
using arma::vec;
using arma::norm;

typedef HarmonicOscillatorWithCoulombInteraction HOWCI;


HOWCI::HarmonicOscillatorWithCoulombInteraction(double omega) :
    HarmonicOscillator(omega) {
}


double HOWCI::evaluateLocalEnergy(mat R) {

    int numberOfParticles  = m_wavefunction->getNumberOfParticles();

    // Compute the oscillator energy.
    double harmonicOscillatorEnergy = HarmonicOscillator::evaluateLocalEnergy(R);

    // Compute the interaction energy.
    double interactionEnergy = 0;
    for (int particle_i = 0; particle_i < numberOfParticles; particle_i++) {
        for (int particle_j = particle_i+1; particle_j < numberOfParticles; particle_j++) {
            vec r_ij = R.row(particle_j).t() - R.row(particle_i).t();
            interactionEnergy += 1 / norm(r_ij);
        }
    }
    return harmonicOscillatorEnergy + interactionEnergy;
}





#include <Hamiltonians/HarmonicOscillator.h>

HarmonicOscillator::HarmonicOscillator() {
}


HarmonicOscillator::HarmonicOscillator(TrialWavefunction* trial) {
    m_wavefunction = trial;
}


double HarmonicOscillator::evaluateLocalEnergy(arma::mat R) {

    // Compute the local kinetic energy.
    arma::mat H       = arma::zeros<arma::mat>(2,2);
    double    h       = 1e-5;
    double    kinetic = 0;

    for (int particle = 0; particle < 2; particle++) {
        for (int coordinate = 0; coordinate < 2; coordinate++) {

            H(particle, coordinate) = h;
            kinetic -= (m_wavefunction->evaluateWavefunction(R+H) - 2 *
                        m_wavefunction->evaluateWavefunction(R)   +
                        m_wavefunction->evaluateWavefunction(R-H)) / (h*h);
            H(particle, coordinate) = 0;

        }
    }
    kinetic /= (2 * m_wavefunction->evaluateWavefunction(R));

    // Compute the local potential energy.
    double    potential;

    for (int particle = 0; particle < 2; particle++) {
        arma::vec position = R.col(particle);
        double    rSquared = dot(position, position);
        potential += rSquared;
    }
    potential /= 2;

    return kinetic;// + potential;
}


void HarmonicOscillator::setTrialWavefunction(TrialWavefunction *trial){
    m_wavefunction = trial;
}




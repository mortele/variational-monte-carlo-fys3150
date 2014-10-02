#include <Hamiltonians/NonInteractingHamiltonian.h>

NonInteractingHamiltonian::NonInteractingHamiltonian(TrialWavefunction* trial) :
    m_waveFunction(trial) {
}


double NonInteractingHamiltonian::evaluateLocalEnergy(arma::vec a, arma::mat R) {

    // Compute the local kinetic energy.
    arma::mat H       = arma::zeros<arma::mat>(2,2);
    double    h       = 1e-5;
    double    kinetic = 0;

    for (int particle = 0; particle < 2; particle++) {
        for (int coordinate = 0; coordinate < 2; coordinate++) {

            H(particle, coordinate) = h;
            kinetic -= (m_waveFunction->evaluateWavefunction(a,R+H) - 2 *
                        m_waveFunction->evaluateWavefunction(a,R)   +
                        m_waveFunction->evaluateWavefunction(a,R-H)) / (h*h);
            H(particle, coordinate) = 0;

        }
    }
    kinetic /= (2 * m_waveFunction->evaluateWavefunction(a,R));

    // Compute the local potential energy.
    arma::vec position1  = R.col(0);
    arma::vec position2  = R.col(1);
    double    r1         = norm(position1);
    double    r2         = norm(position2);
    double    potential;

    for (int particle = 0; particle < 2; particle++) {
        arma::vec position = R.col(particle);
        double    rSquared = dot(position, position);
        potential += rSquared;
    }
    potential /= 2;

    return kinetic + potential;
}



#include <Hamiltonians/HeliumAtom.h>
#include <Hamiltonians/Hamiltonian.h>

using arma::mat;
using arma::vec;
using arma::norm;
using arma::dot;
using std::sqrt;


double HeliumAtom::evaluateLocalEnergy(mat R) {

    // Evalute the kinetic energy.
    double kinetic = Hamiltonian::evaluateLocalEnergy(R);

    // Evaluate the remaining potential terms
    vec position1  = R.row(0).t();
    vec position2  = R.row(1).t();
    vec distance12 = position2 - position1;

    double r1  = norm(position1);
    double r2  = norm(position2);
    double r12 = norm(distance12);
    double potential = 1.0/r12 - 2.0/r1 - 2.0/r2;

    return kinetic + potential;
}


void HeliumAtom::setTrialWavefunction(TrialWavefunction *trial) {
    m_wavefunction = trial;
    m_wavefunction->setOmega(1);
}

#include <Wavefunctions/TwoElectronNonInteracting.h>
#include <Math/RandomNumberGenerator.h>



TwoElectronNonInteracting::TwoElectronNonInteracting() {
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = arma::vec(1);
    m_alpha(0)   = 1.0;
}

TwoElectronNonInteracting::TwoElectronNonInteracting(vec a) {
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = a;
}

double TwoElectronNonInteracting::evaluateWavefunction(arma::mat R) {

    arma::vec position1  = R.row(0).t();
    arma::vec position2  = R.row(1).t();

    double r1  = arma::norm(position1);
    double r2  = arma::norm(position2);

    double waveFunction = exp(-m_omega*m_alpha(0) * (r1*r1 + r2*r2) / 2.0 );
    return waveFunction;
}


mat TwoElectronNonInteracting::setInitialPosition() {
    mat R = mat(m_particles, m_dimensions);
    for (int i = 0; i < m_particles; i++) {
        for (int j = 0; j < m_dimensions; j++) {
            R(i,j) = randomNumberGenerator(m_seed);
        }
    }
    return R;
}






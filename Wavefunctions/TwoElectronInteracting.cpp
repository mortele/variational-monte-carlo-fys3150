#include <Wavefunctions/TwoElectronInteracting.h>
#include <Math/RandomNumberGenerator.cpp>

TwoElectronInteracting::TwoElectronInteracting() {
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = arma::vec(2);
    m_alpha(0)   = 0.9;
    m_alpha(1)   = 0.2;
}


TwoElectronInteracting::TwoElectronInteracting(arma::vec a) {
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = a;
}


double TwoElectronInteracting::evaluateWavefunction(arma::mat R) {

    arma::vec position1  = R.col(0);
    arma::vec position2  = R.col(1);
    arma::vec distance12 = position2 - position1;

    double r1  = arma::norm(position1);
    double r2  = arma::norm(position2);
    double r12 = arma::norm(distance12);

    double waveFunction = exp(-m_omega*m_alpha(0) * (r1*r1 + r2*r2) / 2 ) * exp(r12 / (1 + m_alpha(1)*r12*r12));
    return waveFunction;
}


mat TwoElectronInteracting::setInitialPosition() {

    mat R = mat(2,2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            R(i,j) = randomNumberGenerator(m_seed);
        }
    }
    return R;
}





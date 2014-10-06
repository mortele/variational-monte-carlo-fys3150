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

    arma::vec position1  = R.col(0);
    arma::vec position2  = R.col(1);

    double r1  = arma::norm(position1);
    double r2  = arma::norm(position2);

    double waveFunction = exp(-m_alpha(0) * (r1*r1 + r2*r2) / 2 );
    return waveFunction;
}


mat TwoElectronNonInteracting::setInitialPosition() {
    mat R = mat(2,2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            R(i,j) = 5*randomNumberGenerator(m_seed);
        }
    }
    return R;
}






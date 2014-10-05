#include <Wavefunctions/TwoElectronNonInteracting.h>


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
    return R;
}




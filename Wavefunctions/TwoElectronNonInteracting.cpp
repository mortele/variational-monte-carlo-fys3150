#include <Wavefunctions/TwoElectronNonInteracting.h>


double TwoElectronNonInteracting::evaluateWavefunctionSquared(arma::vec alpha,
                                                              arma::mat R) {

    arma::vec position1  = R.col(0);
    arma::vec position2  = R.col(1);
    arma::vec distance12 = position2 - position1;

    double r1  = arma::norm(position1);
    double r2  = arma::norm(position2);
    double r12 = arma::norm(distance12);

    double waveFunction = exp(-alpha(0) * (r1*r1 + r2*r2) / 2 ) * exp(r12 / (1 + alpha(1)*r12));
    return waveFunction*waveFunction;
}





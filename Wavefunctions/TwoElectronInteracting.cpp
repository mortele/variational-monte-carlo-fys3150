#include <Wavefunctions/TwoElectronInteracting.h>
#include <Math/RandomNumberGenerator.cpp>

using arma::mat;
using arma::vec;
using arma::norm;


TwoElectronInteracting::TwoElectronInteracting(vec a) {
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = a;
}


double TwoElectronInteracting::evaluateWavefunction(mat R) {

    // Compute the standard harmonic oscillator part of the wavefunction.
    double harmonicOscillatorWavefunction = TwoElectronNonInteracting::
                                            evaluateWavefunction(R);

    // Compute the Jastrow factor.
    vec position1  = R.row(0).t();
    vec position2  = R.row(1).t();
    vec distance12 = position2 - position1;

    double r12 = norm(distance12);
    double jastrowFactor = exp(r12 / (1.0 + m_alpha(1)*r12));

    return harmonicOscillatorWavefunction * jastrowFactor;
}



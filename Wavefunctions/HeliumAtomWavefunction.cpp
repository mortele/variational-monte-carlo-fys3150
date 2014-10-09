#include <Wavefunctions/HeliumAtomWavefunction.h>
#include <Math/RandomNumberGenerator.h>


using arma::vec;
using arma::mat;
using arma::norm;


HeliumAtomWavefunction::HeliumAtomWavefunction(vec a) {
    m_oldWaveFunctionSquaredValue = 0;
    m_particles  = 2;
    m_dimensions = 2;
    m_alpha      = a;
}


double HeliumAtomWavefunction::evaluateWavefunction(arma::mat R) {
    vec position1  = R.row(0).t();
    vec position2  = R.row(1).t();
    vec distance12 = position2 - position1;

    double r1  = norm(position1);
    double r2  = norm(position2);
    double r12 = norm(distance12);

    double hydrogenWavefunction = exp(-m_alpha(0) * (r1*r1 + r2*r2));
    double jastrowFactor        = exp(r12 / (2.0*(1.0 + m_alpha(1)*r12)));

    return hydrogenWavefunction * jastrowFactor;
}


arma::mat HeliumAtomWavefunction::setInitialPosition() {
    mat R = mat(m_particles, m_dimensions);
    for (int i = 0; i < m_particles; i++) {
        for (int j = 0; j < m_dimensions; j++) {
            R(i,j) = randomNumberGenerator(m_seed);
        }
    }
    return R;
}







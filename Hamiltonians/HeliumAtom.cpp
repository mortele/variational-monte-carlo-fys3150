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
    double r1r2 = sqrt(dot(position1, position2));
    double a = m_wavefunction->getAlpha()(0);
    double b = m_wavefunction->getAlpha()(1);


    double potential = 1.0/r12 - 2.0/r1 - 2.0/r2;
    //return kinetic + potential;*/

    double A = 1 / (2*(1+b*r12)*(1+b*r12));
    double B = (a*(r1+r2))/(r12) * (1 - r1r2/(r1*r2));
    double C = -A;
    double D = -2/r12;
    double E = 2*b / (1+b*r12);
    double E_L1 = (a-2)*(1/r1+1/r2)+1/r12 - a*a;

    //std::cout << "CF_E=" << E_L1 + A * (B + C + D + E) << ",  N_E=" << potential+kinetic <<
      //           ", kinetic=" << kinetic << std::endl << R << std::endl << std::endl;

    //return E_L1 + A * (B + C + D + E);
    return kinetic + potential;
}


void HeliumAtom::setTrialWavefunction(TrialWavefunction *trial) {
    m_wavefunction = trial;
    m_wavefunction->setOmega(1);
}

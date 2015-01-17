#include "Wavefunctions/WaveFunction.h"
#include <armadillo>

using namespace arma;

WaveFunction::WaveFunction(double a, int N, int Ndim)
{
    this->a = a;
    NumberOfParticles = N;
    NumberOfDimensions = Ndim;
}
double WaveFunction::laplacianLog(vec x)
{
    cout << " error, in parent class 'Wavefunction' " << endl;
    return 0;
}
bool WaveFunction::newStep(mat &xnew, mat x,int &WhichParticle)
{
    cout << " error, in parent class 'Wavefunction' " << endl;
    return true;
}
//void WaveFunction::getSlaterInverse(arma::vec x)
//{
//    cout << " error, in parent class 'Wavefunction' " << endl;
//}
//void WaveFunction::updateSlaterInverse(arma::vec x, int i)
//{
//    cout << " error, in parent class 'Wavefunction' " << endl;
//}
void WaveFunction::setUpForMetropolis(arma::mat &x)
{
    cout << " error, in parent class 'Wavefunction' " << endl;
}

#include "Wavefunctions/Orbital.h"
#include <armadillo>
using namespace arma;
Orbital::Orbital()
{
}
double Orbital::eval(double x, double a) {
    cout << "you are still in the Orbital class, stupid!! EVAL" << endl;
    return 0;
}
double Orbital::gradient(double x, double a)
{
    cout << "you are still in the Orbital class, stupid!! GRAD" << endl;
    return 0;
}
double Orbital::laplacian(double x,double a)
{
    cout << "you are still in the Orbital class, stupid!! LAPLOG" << endl;
    return 0;
}

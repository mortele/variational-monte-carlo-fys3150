#pragma once
#include <Wavefunctions/WaveFunction.h>
#include <Wavefunctions/Orbital.h>




#include <armadillo>
class Slater : public WaveFunction
{
public:
    int whichSlater;
    int splitSlater;
    Slater(double a, int N); // : WaveFunction(a,N) {}
    double a,Rsd;
    int NumberOfParticles; // NB: Number of particles in each slater, i.e. numberOfTotalParticles/2.
    int NumberOfDimensions,acceptanceCounter;
    Orbital* myorbital[5];
    arma::mat slaterInverse[2];
    double laplacianLog(arma::vec x);
    bool newStep(arma::mat &xnew, arma::mat x, int &whichParticle);
    double evaluateSlater(arma::vec x);
    arma::mat calculateSlater(arma::vec x);
    double slaterNumericalLaplacianLog(arma::vec x);
    double slaterAnalyticalLaplacianLog(arma::vec x);
    void getSlaterInverse(arma::vec x);
    void updateSlaterInverse(arma::vec x, int i);
    void setUpForMetropolis(arma::mat &x);
};

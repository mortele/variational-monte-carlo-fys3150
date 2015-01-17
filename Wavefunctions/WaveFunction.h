#pragma once
#include <armadillo>
class WaveFunction
{
public:
double a,Rsd;
int NumberOfParticles,NumberOfDimensions,acceptanceCounter;
WaveFunction(double a, int N, int Ndim);
WaveFunction() {}
virtual double laplacianLog(arma::vec x);
virtual bool newStep(arma::mat &xnew, arma::mat x, int &WhichParticle);
//virtual void getSlaterInverse(arma::vec x);
//virtual void updateSlaterInverse(arma::vec x, int i);
virtual void setUpForMetropolis(arma::mat &x);
};

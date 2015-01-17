#include "Wavefunctions/Slater.h"
#include <armadillo>

using namespace arma;

Slater::Slater(double a, int N) : WaveFunction(a,N,1)
{
    this->a = a;
    this->whichSlater = 0;
    this->splitSlater = 2;

    //    myorbital[0] = new HO0();
    //    myorbital[1] = new HO1();
    //    myorbital[2] = new HO2();
    NumberOfParticles = N/2;
    NumberOfDimensions = 1;
}
double Slater::laplacianLog(vec x)
{
    double analytic = this->slaterAnalyticalLaplacianLog(x);
    // double num = this->slaterNumericalLaplacianLog(x);
    return analytic;
}
bool Slater::newStep(mat &xnew, mat x,int &whichParticle)
{
    this->whichSlater = floor(whichParticle / NumberOfParticles);
    xnew = x;
    vec num = randn<vec>(1);
    vec num2 = randu<vec>(2);
    whichParticle = round(num2(1)*(this->NumberOfParticles-1));
    xnew.row(whichParticle) = x.row(whichParticle) + 2.0/NumberOfParticles*a*num(0); //newstep(x)
    Rsd = 0;
    for(int j = 0;j<NumberOfParticles;j++)
    {
        Rsd += myorbital[j]->eval(xnew(whichParticle),a)*slaterInverse[whichSlater](j,whichParticle);
    }
    bool accept = false;
    if(Rsd*Rsd>num2(0)){
        accept = true;
        acceptanceCounter+=1;
    }
    return accept;
}

double Slater::evaluateSlater(vec x) {
    return det(calculateSlater(x));
}

mat Slater::calculateSlater(vec x) {
    mat Slater = zeros<mat>(NumberOfParticles,NumberOfParticles);
    for(int i = 0;i<NumberOfParticles;i++) {
        for(int j = 0; j<NumberOfParticles;j++) {
            Slater(i,j) = myorbital[j]->eval(x(i+whichSlater*NumberOfParticles),a);
        }
    }
    return Slater;
}

double Slater::slaterNumericalLaplacianLog(vec x)
{
    double h= 0.0001;
    vec mod = zeros<vec>(NumberOfParticles);
    double sum = 0;
    for(int i = 0;i<NumberOfParticles;i++)
    {
        mod(i)+=h;
        sum += this->evaluateSlater(x+mod) +this->evaluateSlater(x-mod);
        mod(i)=0;
    }
    sum/=this->evaluateSlater(x);
    sum -=NumberOfParticles*2;
    sum/=h*h;
    return sum;
}
void Slater::getSlaterInverse(arma::vec x)
{
    for (int i = 0; i < splitSlater; i++) {
        slaterInverse[i] = this->calculateSlater(x);
        slaterInverse[i] = inv(slaterInverse[i]);
    }
}
double Slater::slaterAnalyticalLaplacianLog(arma::vec x)
{
    // we should keep the laplacian wrt all the different particles separately and update only
    // the ones we have moved (or is that correct?)
    double sum = 0;
    for (int k = 0; k < splitSlater; k++) {
        for(int i =0; i<NumberOfParticles;i++) {
            for(int j = 0;j<NumberOfParticles;j++) {
                sum += myorbital[j]->laplacian(x(i),a)*slaterInverse[k](j,i); //for some reason j and i are switched
            }
        }
    }
    return sum;
}

void Slater::updateSlaterInverse(arma::vec x, int i)
{
    mat oldSlater = slaterInverse[whichSlater];
    for (int k = 0;k<NumberOfParticles; k++) {
        for (int j = 0; j<NumberOfParticles; j++) {
            if(j != i) {
                double sum = 0;
                for( int l = 0; l< NumberOfParticles; l++) {
                    sum += oldSlater(l,j) * myorbital[l]->eval(x(i), a);
                }
                slaterInverse[whichSlater](k,j) = oldSlater(k,j) - oldSlater(k,i) * sum / Rsd;
            }
            else {
                slaterInverse[whichSlater](k,j) = oldSlater(k,i)/ Rsd;
            }
        }
    }
}
void Slater::setUpForMetropolis(arma::mat &x)
{
    acceptanceCounter = 0;
    arma_rng::set_seed_random(); // not sure if this helps
    x = a*randn<mat>(this->NumberOfParticles,this->NumberOfDimensions);
    this->getSlaterInverse(x);
}

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <armadillo>
#include <vector>
#include <System.h>

#include <Wavefunctions/TrialWavefunction.h>
#include <Wavefunctions/TwoElectronNonInteracting.h>
#include <Wavefunctions/TwoElectronInteracting.h>

#include <Hamiltonians/Hamiltonian.h>
#include <Hamiltonians/HarmonicOscillator.h>

//#include <Math/RandomNumberGenerator.h>


using namespace std;
using namespace arma;

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.2e-7
#define RNMX (1.0-EPS)

double randomNumberGenerator(long *idum) {
   int            j;
   long           k;
   static long    idum2 = 123456789;
   static long    iy=0;
   static long    iv[NTAB];
   double         temp;

   if(*idum <= 0) {
      if(-(*idum) < 1) *idum = 1;
      else             *idum = -(*idum);
      idum2 = (*idum);
      for(j = NTAB + 7; j >= 0; j--) {
         k     = (*idum)/IQ1;
     *idum = IA1*(*idum - k*IQ1) - k*IR1;
     if(*idum < 0) *idum +=  IM1;
     if(j < NTAB)  iv[j]  = *idum;
      }
      iy=iv[0];
   }
   k     = (*idum)/IQ1;
   *idum = IA1*(*idum - k*IQ1) - k*IR1;
   if(*idum < 0) *idum += IM1;
   k     = idum2/IQ2;
   idum2 = IA2*(idum2 - k*IQ2) - k*IR2;
   if(idum2 < 0) idum2 += IM2;
   j     = iy/NDIV;
   iy    = iv[j] - idum2;
   iv[j] = *idum;
   if(iy < 1) iy += IMM1;
   if((temp = AM*iy) > RNMX) return RNMX;
   else return temp;
}
#undef IM1
#undef IM2
#undef AM
#undef IMM1
#undef IA1
#undef IA2
#undef IQ1
#undef IQ2
#undef IR1
#undef IR2
#undef NTAB
#undef NDIV
#undef EPS
#undef RNMX


int main(int argc, char* argv[]) {

    long   seed = -1;
    double dx   = pow(10, -4);
    int    N    = pow(10, 5);
    int    M    = floor(N/5);

    System system;
    system.setTrialWavefunction(new TwoElectronNonInteracting);
    system.setHamiltonian      (new HarmonicOscillator);
    system.setRandomNumberGeneratorSeed(&seed);
    system.setUpMetropolis(N, M, dx);


    cout << randomNumberGenerator(&seed) << endl;



    TwoElectronNonInteracting trial;
    HarmonicOscillator H(&trial);

    mat R     = randu<mat>(2,2);
    vec alpha = ones<vec>(1);

    trial.setAlpha(alpha);

    double stepSize = 0.0005;
    double energy = 0;

    trial.setOldWaveFunctionSquared(trial.evaluateWavefunction(R) *
                                    trial.evaluateWavefunction(R));


    srand(2); // Sets the random number generator seed.
    int accepted = 0;

    for (int step = 0; step < N; step++) {
        mat Rnew = R;
        int randomParticle   = rand() % 2;
        int randomCoordinate = rand() % 2;
        double randomStep    = (((double) rand() / (double) RAND_MAX)*2-1) * stepSize;

        Rnew(randomParticle, randomCoordinate) += randomStep;
        double newWavefunctionSquared = pow(trial.evaluateWavefunction(Rnew), 2);
        double oldWavefunctionSquared = trial.getOldWaveFunctionSquared();

        if (newWavefunctionSquared > oldWavefunctionSquared) {
            R = Rnew;
            trial.setOldWaveFunctionSquared(newWavefunctionSquared);
            if (step >= M) accepted++;
        } else {
            double acceptanceRatio = (double) rand() / (double) RAND_MAX; // uniform random, (0,1]
            if (acceptanceRatio > newWavefunctionSquared / oldWavefunctionSquared) {
                R = Rnew;
                trial.setOldWaveFunctionSquared(newWavefunctionSquared);
                if (step >= M) accepted++;
            }
        }

        printf("Progress: %10.2f %% \r", 100.0*step/(double)N);
        fflush(stdout);

        if (step >= M) {
            energy += H.evaluateLocalEnergy(R);
        }
    }

    printf("=========================================\n");
    printf("================finished!================\n");
    printf("=========================================\n");
    printf("Energy                  = %15.6f\n",   energy / ((double) (N-M)));
    printf("Ratio of accepted steps = %15.6f\n\n", accepted / ((double) (N-M)));

    // Program run successfully.
    return 0;
}


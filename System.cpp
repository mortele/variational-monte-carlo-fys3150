#include <System.h>
#include <Hamiltonians/Hamiltonian.h>
#include <Wavefunctions/WaveFunction.h>
#include <Math/RandomNumberGenerator.h>
#include <StatisticsSampler.h>
#include <timing.h>

typedef unsigned long long int ullint;

using arma::vec;
using arma::mat;


System::System() {
    m_statisticsSampler = new StatisticsSampler(this);
}


void System::setTrialWavefunction(WaveFunction *trial) {
    m_wavefunction = trial;
}


void System::setHamiltonian(Hamiltonian *hamiltonian) {
    m_hamiltonian = hamiltonian;
    m_hamiltonian->setTrialWavefunction(m_wavefunction);
}


void System::setAlpha(vec a) {
    //m_wavefunction->setAlpha(a);
}


void System::setUpMetropolis(int    N,
                             int    M,
                             double dx,
                             bool   storeOneBody=false) {
    m_N  = N;
    m_M  = M;
    m_dx = dx;
    m_particles  = m_wavefunction->NumberOfParticles;
    m_dimensions = m_wavefunction->NumberOfDimensions;
    //m_R = m_wavefunction->setInitialPosition();
    /*m_wavefunction->setOldWaveFunctionSquared(
                    pow(m_wavefunction->evaluateWavefunction(m_R),2));
*/
    m_statisticsSampler->setStoreOneBody(storeOneBody);
}


void System::setRandomNumberGeneratorSeed(long *seed) {
    m_seed = seed;
    //m_wavefunction->setRandomNumberGeneratorSeed(seed);
}


StatisticsSampler* System::runMetropolisAlgorithm(bool printProgress) {
    ullint startTime = unixTimeInMicroseconds();

    switch (printProgress) {
        case true : {
            for (int i = 0; i < m_M; i++) {
                this->metropolisStep();
                if (i % 1000 == 0) printf("Progress: %10.1f %% \r",
                                          100*((double)i/((double)m_N)));
            }
            for (int i = m_M; i < m_N; i++) {
                bool accepted = this->metropolisStep();
                m_statisticsSampler->sample(accepted);
                if (i % 1000 == 0) printf("Progress: %10.1f %% \r",
                                          100*((double)i/((double)m_N)));
            }
            printf("==================================================\n");
            printf("=================== Finished ! ===================\n");
            printf("==================================================\n\n");
            break;

        } case false : {
            for (int i = 0; i < m_M; i++) {
                this->metropolisStep();
            }
            for (int i = m_M; i < m_N; i++) {
                bool accepted = this->metropolisStep();
                m_statisticsSampler->sample(accepted);
            }
        }
    }
    m_executionTime = (unixTimeInMicroseconds() - startTime) / 1000000.0;
    return m_statisticsSampler;
}


bool System::metropolisStep() {

    int    randomCoordinate, randomParticle;

    // Change the position of a single coordinate for a single particle.
    randomCoordinate = floor(randomNumberGenerator(m_seed) * m_dimensions);
    randomParticle   = floor(randomNumberGenerator(m_seed) * m_particles);

    mat newR = m_R;
    newR(randomParticle,randomCoordinate)+= randomNumberGeneratorNormal(m_seed)
                                            * m_dx;


    //newR(randomParticle,randomCoordinate)+=((randomNumberGenerator(m_seed)*2)
    //                                        - 1) * m_dx;

    /*double newWavefunctionSquared = pow(m_wavefunction->
                                        evaluateWavefunction(newR), 2);
    double oldWavefunctionSquared = m_wavefunction->
                                    getOldWaveFunctionSquared();
*/
    // Check if the new position is prefered.
    /*if (newWavefunctionSquared > oldWavefunctionSquared) {
        m_R = newR;
        m_wavefunction->setOldWaveFunctionSquared(newWavefunctionSquared);
        return true;
    } else {
        // If not, accept the new position with probability newWavefunction^2
        // / oldWavefunction^2.
        if (randomNumberGenerator(m_seed) < (newWavefunctionSquared /
                                             oldWavefunctionSquared)) {
            m_R = newR;
            m_wavefunction->setOldWaveFunctionSquared(newWavefunctionSquared);
            return true;
        } else {
            return false;
        }
    }*/
}

void System::setNumberOfDimensions(int numberOfDimensions) {
    m_dimensions = numberOfDimensions;
    //m_wavefunction->setNumberOfDimensions(numberOfDimensions);
}

#include <StatisticsSampler.h>
#include <System.h>
#include <Hamiltonians/Hamiltonian.h>
#include <iostream>
#include <fstream>

using std::fstream;
using std::ios;
using std::endl;


StatisticsSampler::StatisticsSampler(System *system) :
    m_N                  (0),
    m_M                  (0),
    m_storeOneBody       (false),
    m_positionsFileOpened(false),
    m_energy             (0),
    m_energySquared      (0),
    m_accepted           (0),
    m_dx                 (0) {

    m_system = system;
}


void StatisticsSampler::sample(bool accepted) {
    double energy    = m_system->m_hamiltonian->evaluateLocalEnergy(m_system->m_R);
    m_energy        += energy;
    m_energySquared += energy*energy;
    m_accepted      += accepted;

    if (m_storeOneBody) this->storePositions();

}


void StatisticsSampler::printDataToTerminal(unsigned long long int totalTime) {
    this->m_N  = m_system->m_N;
    this->m_M  = m_system->m_M;
    this->m_dx = m_system->m_dx;

    double energy        = m_energy        / ((double) (m_N - m_M));
    double accepted      = m_accepted      / ((double) (m_N - m_M));
    double energySquared = m_energySquared / ((double) (m_N - m_M));

    printf("Energy:                    %25.15g\n", energy);
    printf("Variance:                  %25.15g\n", energySquared - energy*energy);
    printf("Ratio of accepted steps:   %25.5g \n", accepted);
    printf("Execution time:          %25.5g s \n", m_system->m_executionTime);
    printf("(Total time:             %25.5g s)\n", totalTime / 1000000.0 );

}


void StatisticsSampler::printDataToFile(const char* fileName) {
    this->m_N  = m_system->m_N;
    this->m_M  = m_system->m_M;
    this->m_dx = m_system->m_dx;

    double energy        = m_energy        / ((double) (m_N - m_M));
    double accepted      = m_accepted      / ((double) (m_N - m_M));
    double energySquared = m_energySquared / ((double) (m_N - m_M));

    fstream outFile;
    outFile.open(fileName, ios::out);

    outFile << this->m_N                     << " ";
    outFile << this->m_M                     << " ";
    outFile << this->m_dx                    << " ";
    outFile << accepted                      << " ";
    outFile << energy                        << " ";
    outFile << energySquared                 << " ";
    outFile << energySquared - energy*energy << " ";

    outFile.close();
}


void StatisticsSampler::storePositions() {

    // If this is the first time the method is called, open the file.
    if (!m_positionsFileOpened) {
        m_positionsFile.open("oneBody.dat", ios::out);
        m_positionsFileOpened = true;

        // Dump the number of particles and the number of dimensions (on lines one and
        // two) to file, (number of dimensions * number of particles) times. This is
        // done so that we can easily use the MATLAB function load() on the file later.
        for (int i = 0; i < m_system->m_dimensions*m_system->m_particles; i++) {
            m_positionsFile << m_system->m_particles << " ";
        }
        m_positionsFile << endl;
        for (int i = 0; i < m_system->m_dimensions*m_system->m_particles; i++) {
            m_positionsFile << m_system->m_dimensions << " ";
        }
        m_positionsFile << endl;

    }
    for (int i = 0; i < m_system->m_particles; i++) {
        for (int j = 0; j < m_system->m_dimensions; j++) {
            m_positionsFile << m_system->m_R(i,j) << " ";
        }
    }
    m_positionsFile << endl;
}











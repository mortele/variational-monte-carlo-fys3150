#include <StatisticsSampler.h>
#include <System.h>
#include <Hamiltonians/Hamiltonian.h>
#include <iostream>
#include <fstream>

using std::fstream;
using std::ios;


StatisticsSampler::StatisticsSampler(System *system) :
    m_energy(0), m_energySquared(0), m_accepted(0), m_N(0), m_M(0), m_dx(0) {
    m_system = system;
}


void StatisticsSampler::sample(bool accepted) {
    double energy = m_system->m_hamiltonian->evaluateLocalEnergy(m_system->m_R);
    std::cout << energy << "\n";
    m_energy        += energy;
    m_energySquared += energy*energy;
    m_accepted      += accepted;

}


void StatisticsSampler::printDataToTerminal() {
    this->m_N  = m_system->m_N;
    this->m_M  = m_system->m_M;
    this->m_dx = m_system->m_dx;

    double energy        = m_energy        / ((double) (m_N - m_M));
    double accepted      = m_accepted      / ((double) (m_N - m_M));
    double energySquared = m_energySquared / ((double) (m_N - m_M));

    printf("Energy:                   %15.7f\n",   energy);
    printf("Variance:                 %15.7f\n",   energySquared - energy*energy);
    printf("Ratio of accepted steps:  %15.7f\n\n", accepted);

}


void StatisticsSampler::printDataToFile(char* fileName) {
    this->m_N  = m_system->m_N;
    this->m_M  = m_system->m_M;
    this->m_dx = m_system->m_dx;

    fstream outFile;
    outFile.open(fileName, ios::out);
    outFile << "hei";
    outFile.close();
}

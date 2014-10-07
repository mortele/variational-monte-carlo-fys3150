#pragma once
#include <armadillo>
#include <fstream>

class System;


class StatisticsSampler {

private:

    int     m_N;
    int     m_M;
    bool    m_storeOneBody;
    bool    m_positionsFileOpened;
    double  m_energy;
    double  m_energySquared;
    double  m_accepted;
    double  m_dx;
    System*      m_system;
    std::fstream m_positionsFile;

public:
    StatisticsSampler(System* system);
    ~StatisticsSampler() {if (m_positionsFileOpened) m_positionsFile.close();}

    void sample(bool accepted);
    void printDataToTerminal(unsigned long long int totalTime);
    void printDataToFile(const char* fileName);
    void setStoreOneBody(bool storeOneBody) {m_storeOneBody = storeOneBody;}
    void storePositions();
};


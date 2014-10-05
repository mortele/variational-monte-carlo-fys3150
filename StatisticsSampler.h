#pragma once

class System;


class StatisticsSampler {
private:

    double m_energy;
    double m_energySquared;
    double m_accepted;
    double m_dx;
    int m_N;
    int m_M;


    System* m_system;

public:
    StatisticsSampler(System* system);
    ~StatisticsSampler() {}

    void sample(bool accepted);
    void printDataToTerminal();
    void printDataToFile(char* fileName);
};


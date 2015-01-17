TEMPLATE = app
CONFIG  += console
CONFIG  -= app_bundle
CONFIG  -= qt
LIBS    += -larmadillo -lblas -llapack -lrt

SOURCES += main.cpp \
    Wavefunctions/TrialWavefunction.cpp \
    Wavefunctions/TwoElectronNonInteracting.cpp \
    Hamiltonians/Hamiltonian.cpp \
    System.cpp \
    Wavefunctions/TwoElectronInteracting.cpp \
    Math/RandomNumberGenerator.cpp \
    StatisticsSampler.cpp \
    timing.cpp \
    Wavefunctions/HeliumAtomWavefunction.cpp \
    Wavefunctions/WaveFunction.cpp \
    Wavefunctions/Slater.cpp \
    Wavefunctions/Orbital.cpp


HEADERS += \
    Wavefunctions/TrialWavefunction.h \
    Wavefunctions/TwoElectronNonInteracting.h \
    Hamiltonians/Hamiltonian.h \
    System.h \
    Wavefunctions/TwoElectronInteracting.h \
    Math/RandomNumberGenerator.h \
    StatisticsSampler.h \
    timing.h \
    Wavefunctions/HeliumAtomWavefunction.h \
    Wavefunctions/WaveFunction.h \
    Wavefunctions/Slater.h \
    Wavefunctions/Orbital.h


#CONFIG  += c++11
#QMAKE_CXXFLAGS += -std=c++0x


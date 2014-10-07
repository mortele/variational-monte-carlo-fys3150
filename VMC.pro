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
    Hamiltonians/HarmonicOscillator.cpp \
    Wavefunctions/TwoElectronInteracting.cpp \
    Math/RandomNumberGenerator.cpp \
    StatisticsSampler.cpp \
    Hamiltonians/HarmonicOscillatorWithCoulombInteraction.cpp \
    timing.cpp \
    Hamiltonians/HeliumAtom.cpp


HEADERS += \
    Wavefunctions/TrialWavefunction.h \
    Wavefunctions/TwoElectronNonInteracting.h \
    Hamiltonians/Hamiltonian.h \
    System.h \
    Hamiltonians/HarmonicOscillator.h \
    Wavefunctions/TwoElectronInteracting.h \
    Math/RandomNumberGenerator.h \
    StatisticsSampler.h \
    Hamiltonians/HarmonicOscillatorWithCoulombInteraction.h \
    timing.h \
    Hamiltonians/HeliumAtom.h


#CONFIG  += c++11
#QMAKE_CXXFLAGS += -std=c++0x


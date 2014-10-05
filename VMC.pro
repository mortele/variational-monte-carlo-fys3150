TEMPLATE = app
CONFIG  += console
CONFIG  -= app_bundle
CONFIG  -= qt
LIBS    += -larmadillo -lblas -llapack

SOURCES += main.cpp \
    Wavefunctions/TrialWavefunction.cpp \
    Wavefunctions/TwoElectronNonInteracting.cpp \
    Hamiltonians/Hamiltonian.cpp \
    System.cpp \
    Hamiltonians/HarmonicOscillator.cpp \
    Wavefunctions/TwoElectronInteracting.cpp \
    Math/RandomNumberGenerator.cpp \
    StatisticsSampler.cpp


HEADERS += \
    Wavefunctions/TrialWavefunction.h \
    Wavefunctions/TwoElectronNonInteracting.h \
    Hamiltonians/Hamiltonian.h \
    System.h \
    Hamiltonians/HarmonicOscillator.h \
    Wavefunctions/TwoElectronInteracting.h \
    Math/RandomNumberGenerator.h \
    StatisticsSampler.h


#CONFIG  += c++11
#QMAKE_CXXFLAGS += -std=c++0x


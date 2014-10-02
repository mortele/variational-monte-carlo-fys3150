TEMPLATE = app
CONFIG  += console
CONFIG  -= app_bundle
CONFIG  -= qt
LIBS    += -larmadillo -lblas -llapack

SOURCES += main.cpp \
    Wavefunctions/TrialWavefunction.cpp \
    Wavefunctions/TwoElectronNonInteracting.cpp \
    Hamiltonians/Hamiltonian.cpp \
    Hamiltonians/NonInteractingHamiltonian.cpp


HEADERS += \
    Wavefunctions/TrialWavefunction.h \
    Wavefunctions/TwoElectronNonInteracting.h \
    Hamiltonians/Hamiltonian.h \
    Hamiltonians/NonInteractingHamiltonian.h

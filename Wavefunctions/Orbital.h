#pragma once
class Orbital
{
public:
    Orbital();
    virtual double eval(double x,double a);
    virtual double gradient(double x, double a);
    virtual double laplacian(double x, double a);
};

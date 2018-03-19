//
// Created by Sathyam Vellal on 17/03/2018.
//

#include "spring1d/spring1d.h"

Spring1D::Spring1D(double k, double m, double x0)
        : k(k), m(m), x0(x0) {}

Spring1D::Spring1D(const Spring1D &spring1D)
        : Spring1D(spring1D.k, spring1D.m, spring1D.x0) {}

Spring1D Spring1D::operator=(const Spring1D &spring1D)
{
    return *this;
}

Spring1D::~Spring1D()
{
    // Nothing to do here
}

double Spring1D::getX()
{
    return x;
}

void Spring1D::setX(double x)
{
    this->x = x;
}
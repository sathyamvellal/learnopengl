//
// Created by Sathyam Vellal on 17/03/2018.
//

#include "spring1d/spring1d.h"

Spring1D::Spring1D(double k)
        : k(k) {}

Spring1D::Spring1D(const Spring1D &spring1D)
        : Spring1D(spring1D.k) {}

Spring1D Spring1D::operator=(const Spring1D &spring1D)
{
    return *this;
}

Spring1D::~Spring1D()
{
    // Nothing to do here
}

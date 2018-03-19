//
// Created by Sathyam Vellal on 18/03/2018.
//

#include "spring1d/spring1d.h"

#include "spring1d/spring1dsim.h"

Spring1DSim::Spring1DSim(const Spring1D &spring1D)
        : spring1D(spring1D) {}

Spring1DSim::Spring1DSim(double k, double m, double x0)
        : Spring1DSim(Spring1D(k, m, x0)) {}

Spring1DSim::Spring1DSim(const Spring1DSim &spring1Dsim)
        : spring1D(spring1Dsim.spring1D) {}

Spring1DSim Spring1DSim::operator=(const Spring1DSim &spring1DSim)
{
    return *this;
}

Spring1DSim::~Spring1DSim()
{
    // Nothing to do here
}

const Spring1D& Spring1DSim::getSpring()
{
    return spring1D;
}

void Spring1DSim::run()
{
    // TODO: simulation runs here
}

void Spring1DSim::step()
{
    // TODO: simulation takes a step here
}

void Spring1DSim::reset()
{
    // TODO: simulation resets here
}
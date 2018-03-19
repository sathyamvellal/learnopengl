//
// Created by Sathyam Vellal on 18/03/2018.
//

#include "utils/logger.h"
#include "spring1d/spring1d.h"

#include "spring1d/spring1dsim.h"

Spring1DSim::Spring1DSim(const Spring1D &spring1D, double dt, double m, double x0)
        : spring1D(spring1D), dt(dt), m(m), x0(x0) {}

Spring1DSim::Spring1DSim(const Spring1D &spring1D, double dt, double m)
        : Spring1DSim(spring1D, dt, m, 0.0) {}

Spring1DSim::Spring1DSim(const Spring1D &spring1D, double dt)
        : Spring1DSim(spring1D, dt, 0.0, 0.0) {}

Spring1DSim::Spring1DSim(const Spring1D &spring1D)
        : Spring1DSim(spring1D, 1.0/30, 0.0, 0.0) {}

Spring1DSim::Spring1DSim(const Spring1DSim &spring1Dsim)
        : spring1D(spring1Dsim.spring1D), dt(spring1Dsim.dt), m(spring1Dsim.m), x0(spring1Dsim.x0) {}

Spring1DSim Spring1DSim::operator=(const Spring1DSim &spring1DSim)
{
    return *this;
}

Spring1DSim::~Spring1DSim()
{
    // Nothing to do here
}

double Spring1DSim::getTimeStep()
{
    return dt;
}

void Spring1DSim::setTimeStep(double dt)
{
    this->dt = dt;
}

double Spring1DSim::getMass()
{
    return m;
}

void Spring1DSim::setMass(double m)
{
    this->m = m;
}

void Spring1DSim::attachMass(double m)
{
    this->m += m;
}

double Spring1DSim::getRestLength()
{
    return x0;
}

void Spring1DSim::setRestLength(double x0)
{
    this->x0 = x0;
}

const Spring1D& Spring1DSim::getSpring()
{
    return spring1D;
}

void Spring1DSim::applyForceField(double fField)
{
    this->fField = fField;
}

void Spring1DSim::init() {
    fTotal = 0.0;
    fField = 0.0;
    fHook = 0.0;
    fDamp = 0.0;

    a = 0.0;
    v = 0.0;
    x = x0;
}

void Spring1DSim::run()
{
    // TODO: simulation runs here
}

void Spring1DSim::step()
{
    // TODO: simulation takes a step here
    // Perform an Euler step
    double dv, dx;

    // Calculate each force
    fField = m * 9.8;
    fHook = spring1D.k * (x - x0) * (x > x0 ? -1 : 1);

    // Calculate total force
    fTotal = fField + fHook + fDamp;

    // Calculate acceleration
    a = fTotal / m;
    dv = a * dt;
    v = v + dv;
    dx = v * dt;
    x = x + dx;

    log<LOG_VERBOSE>("fField: %1%, fHook: %2%, a: %3%, v: %4%, x: %5%") % fField % fHook % a % v % x;
}

void Spring1DSim::reset()
{
    // TODO: simulation resets here
}
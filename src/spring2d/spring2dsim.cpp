//
// Created by Sathyam Vellal on 19/03/2018.
//

#include "utils/logger.h"
#include "spring2d/spring2d.h"

#include "spring2d/spring2dsim.h"

Spring2DSim::Spring2DSim(const Spring2D &spring2D)
        : spring2D(spring2D) {}

Spring2DSim::Spring2DSim(const Spring2DSim &spring2DSim)
        : spring2D(spring2DSim.spring2D) {}

Spring2DSim Spring2DSim::operator=(const Spring2DSim &spring2DSim)
{
    return *this;
}

Spring2DSim::~Spring2DSim()
{
    // Nothing to do here
}

void Spring2DSim::init()
{
    // TODO: init here
}

void Spring2DSim::run()
{
    // TODO: run simulation here
}

void Spring2DSim::step()
{
    // TODO: run simulation step here
}

void Spring2DSim::reset()
{
    // TODO: reset simulation here
}

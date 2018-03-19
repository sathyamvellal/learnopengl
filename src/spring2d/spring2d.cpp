//
// Created by Sathyam Vellal on 19/03/2018.
//

#include "spring2d/spring2d.h"

Spring2D::Spring2D(double kElastic, double kDamp)
        : kElastic(kElastic), kDamp(kDamp) {}

Spring2D::Spring2D(double kElastic)
        : Spring2D(kElastic, 0.0) {}

Spring2D::Spring2D(const Spring2D &spring2D)
        : kElastic(spring2D.kElastic), kDamp(spring2D.kDamp) {}

Spring2D Spring2D::operator=(const Spring2D &spring2D)
{
    return *this;
}

Spring2D::~Spring2D()
{
    // Nothing to do here
}

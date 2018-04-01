//
// Created by Sathyam Vellal on 18/03/2018.
//

#ifndef LEARNOPENGL_SPRING1DSIM_H
#define LEARNOPENGL_SPRING1DSIM_H

#include "spring1d/spring1d.h"

class Spring1DSim {
public:
    Spring1DSim(const Spring1D& spring1D, double dt, double m, double x0);
    Spring1DSim(const Spring1D& spring1D, double dt, double m);
    Spring1DSim(const Spring1D& spring1D, double dt);
    Spring1DSim(const Spring1D& spring1D);
    Spring1DSim(const Spring1DSim &spring1DSim);
    Spring1DSim operator=(const Spring1DSim &spring1DSim);
    ~Spring1DSim();

    double getTimeStep();
    void setTimeStep(double dt);
    double getMass();
    void setMass(double m);
    void attachMass(double m);
    double getRestLength();
    void setRestLength(double x0);

    const Spring1D& getSpring();
    void applyForceField(double fField);

    void init();
    void run();
    void step();
    void reset();
public:
    const Spring1D spring1D;
    double m;
    double x, x0;
    double fTotal, fField, fHook, fDamp, fInst;
    double dt, a, v;
};

#endif //LEARNOPENGL_SPRING1DSIM_H

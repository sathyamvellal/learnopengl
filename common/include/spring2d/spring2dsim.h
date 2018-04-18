//
// Created by Sathyam Vellal on 19/03/2018.
//

#ifndef LEARNOPENGL_SPRING2DSIM_H
#define LEARNOPENGL_SPRING2DSIM_H

#include "spring2d/spring2d.h"

class Spring2DSim
{
public:
    Spring2DSim(const Spring2D &Spring2D);
    Spring2DSim(const Spring2DSim &spring2DSim);
    Spring2DSim operator=(const Spring2DSim &spring2DSim);
    ~Spring2DSim();

    void init();
    void run();
    void step();
    void reset();

public:
    const Spring2D spring2D;

private:

};

#endif //LEARNOPENGL_SPRING2DSIM_H

//
// Created by Sathyam Vellal on 17/03/2018.
//

#include <iostream>

#include "utils/logger.h"

#include "spring1d/spring1d.h"
#include "spring1d/spring1dsim.h"

int main(int argc, char **argv)
{
    log<LOG_VERBOSE>("Hello World");
    Spring1DSim spring1DSim(Spring1D(10.0));

    spring1DSim.attachMass(1.0);
    spring1DSim.setRestLength(10.0);

    spring1DSim.init();

    for (int i = 0; i < 200; ++i) {
        spring1DSim.step();
    }

    return 0;
}
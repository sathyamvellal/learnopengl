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
    Spring1DSim spring1DSim(Spring1D(5.0, 1.0, 2.0));

    return 0;
}
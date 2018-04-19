//
// Created by Sathyam Vellal on 19/04/2018.
//

#include <cstdlib>
#include <random>

#include "utils/random.h"

double drand()
{
#if 1
    static std::default_random_engine generator;
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
#else
    return (double) rand() / RAND_MAX;
#endif
}

int signrand()
{
    return drand() > 0.5 ? 1 : -1;
}

double signdrand()
{
    return signrand() * drand();
}
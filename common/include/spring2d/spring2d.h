//
// Created by Sathyam Vellal on 19/03/2018.
//

#ifndef LEARNOPENGL_SPRING2D_H
#define LEARNOPENGL_SPRING2D_H

// Forward declaration
class Spring2DSim;

class Spring2D
{
public:
    Spring2D(double kElastic, double kDamp);
    Spring2D(double kElastic);
    Spring2D(const Spring2D &spring2D);
    Spring2D operator=(const Spring2D &spring2D);
    ~Spring2D();

public:
    const double kElastic;
    const double kDamp;
};

#endif //LEARNOPENGL_SPRING2D_H

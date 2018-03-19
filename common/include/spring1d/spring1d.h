//
// Created by Sathyam Vellal on 17/03/2018.
//

#ifndef LEARNOPENGL_SPRING1D_H
#define LEARNOPENGL_SPRING1D_H

// Forward declaration
class Spring1DSim;

class Spring1D
{
private:
    friend class Spring1DSim;
public:
    Spring1D(double k);
    Spring1D(const Spring1D &spring1D);
    Spring1D operator=(const Spring1D &spring1D);
    ~Spring1D();

    double reset();

public:
    const double k;

private:
    double x;
};

#endif //LEARNOPENGL_SPRING1D_H

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
    Spring1D(double k, double m, double x0);
    Spring1D(const Spring1D &spring1D);
    Spring1D operator=(const Spring1D &spring1D);
    ~Spring1D();

    double getX();
    void setX(double x);

    double reset();

public:
    const double k;
    const double m;
    const double x0;

private:
    double x;
};

#endif //LEARNOPENGL_SPRING1D_H

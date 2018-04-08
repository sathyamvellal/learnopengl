//
// Created by Sathyam Vellal on 07/03/2018.
//

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "particleflow/particleflow.h"

#define MAX_POS 1.0

int nVertices;

#if 0
float vertices2[NVERTICES][3] = {
        { -0.4f,  0.2f,  0.0f },
        {  0.5f,  0.0f,  0.0f }
};

float velocities2[NVERTICES][3] = {
        0, 0, 0,
        0, 0, 0
};

float dir[NVERTICES][3] = {
         1,  1,  1
        -1, -1, -1
};

float *vertices1 = &vertices2[0][0];
#endif

float **vertices2;
float *vertices1;
float **velocities2;
float *velocities1;
glm::vec3 o;

void random(int i) {
    vertices2[i][X] = (float) rand() / RAND_MAX * 2 - 1.0f;
    vertices2[i][Y] = (float) rand() / RAND_MAX * 2 - 1.0f;
    velocities2[i][X] = velocities2[i][Y] = 0.0f;
}

void hit(int i, float x, float y) {
    if (vertices2[i][X] >  x) { velocities2[i][X] *= -1; vertices2[i][X] =  x - 0.01f; }
    if (vertices2[i][X] < -x) { velocities2[i][X] *= -1; vertices2[i][X] = -x + 0.01f; }
    if (vertices2[i][Y] >  y) { velocities2[i][X] *= -1; vertices2[i][Y] =  y - 0.01f; }
    if (vertices2[i][Y] < -y) { velocities2[i][X] *= -1; vertices2[i][Y] = -y + 0.01f; }
}

void wrap(int i) {
    if (vertices2[i][X] >  1.0) vertices2[i][X] = -1.0;
    if (vertices2[i][X] < -1.0) vertices2[i][X] =  1.0;
    if (vertices2[i][Y] >  1.0) vertices2[i][Y] = -1.0;
    if (vertices2[i][Y] < -1.0) vertices2[i][Y] =  1.0;
}

void check(int i) {
    if (fabs(vertices2[i][X]) > 1.0 || fabs(vertices2[i][Y]) > 1.0
            || fabs(velocities2[i][X]) > 2.0 || fabs(velocities2[i][Y]) > 2.0) {
        random(i);
    }
}

void init()
{
    nVertices = 100000;

    vertices1 = new float[3 * nVertices];
    velocities1 = new float[3 * nVertices];
    srand(time(NULL));
    rand();

    vertices2 = new float*[nVertices];
    velocities2 = new float*[nVertices];
    for (int i = 0; i < nVertices; ++i) {
        vertices2[i] = &vertices1[3 * i];
        velocities2[i] = &velocities1[3 * i];
        vertices2[i][X] = (float) rand() / RAND_MAX * 2 - 1.0f;
        vertices2[i][Y] = (float) rand() / RAND_MAX * 2 - 1.0f;
        vertices2[i][Z] = 0.0f;

        velocities2[i][X] = velocities2[i][Y] = velocities2[i][Z] = 0.0f;
    }

    for (int i = 0; i < nVertices; ++i) {
        // std::cout << "(" << vertices2[i][X] << ", " << vertices2[i][Y] << ", " << vertices2[i][Z] << ")" << std::endl;
        // std::cout << "(" << vertices1[3 * i + X] << ", " << vertices1[3 * i + Y] << ", " << vertices1[3 * i + Z]  << ")" << std::endl;
    }

    o = glm::vec3((float) rand() / RAND_MAX, (float) rand() / RAND_MAX, 0.0f);
}

void step()
{
    for (int i = 0; i < nVertices; ++i) {
        glm::vec3 p = glm::make_vec3(&vertices2[i][0]);
        glm::vec3 q = p - o;
        float d = glm::dot(q, q);
        float dd = exp(-d*d);
        float dx, dy;
        glm::vec3 a;

        if (d > 0.1) {
            a.x = dd * 0.0075 * ((p.x - o.x) > 0 ? -1 : 1);
            a.y = dd * 0.0075 * ((p.y - o.y) > 0 ? -1 : 1);
        } else if (d > 0.01) {
            a.x = dd * 0.05 * ((p.x - o.x) > 0 ? 1 : -1);
            a.y = dd * 0.05 * ((p.y - o.y) > 0 ? 1 : -1);
            velocities2[i][X] *= 0.9;
            velocities2[i][Y] *= 0.9;
        } else {
            a.x = dd * ((p.x - o.x) > 0 ? 1 : -1);
            a.y = dd * ((p.y - o.y) > 0 ? 1 : -1);
        }

        velocities2[i][X] += a.x;
        velocities2[i][Y] += a.y;

        dx = (0.01 * velocities2[i][X] * fabs(p.x - o.x) / d);
        dy = (0.01 * velocities2[i][Y] * fabs(p.y - o.y) / d);

        vertices2[i][X] += dx;
        vertices2[i][Y] += dy;

        wrap(i);

        check(i);
    }
}
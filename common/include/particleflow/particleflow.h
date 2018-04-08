//
// Created by Sathyam Vellal on 07/05/2018.
//

#ifndef CS520_PARTICLEFLOW_H
#define CS520_PARTICLEFLOW_H

#include <glm/glm.hpp>

#define X 0
#define Y 1
#define Z 2
#define W 3

#define NVERTICES 2

extern int nVertices;
#if 0
extern float vertices2[NVERTICES][3];
extern float *vertices1;
extern float dir[NVERTICES][3];
#endif
extern float **vertices2;
extern float *vertices1;
extern float **velocities2;
extern float *velocities1;
extern glm::vec3 o;

void init();
void step();

#endif //CS520_PARTICLE_FLOW
